/* Copyright (c) 2008-2011, Avian Contributors

   Permission to use, copy, modify, and/or distribute this software
   for any purpose with or without fee is hereby granted, provided
   that the above copyright notice and this permission notice appear
   in all copies.

   There is NO WARRANTY for this software.  See license.txt for
   details. */

extern "C" {
  #include <gdb/jit-reader.h>

  GDB_DECLARE_GPL_COMPATIBLE_READER
}
#include <stdio.h>

#include "common.h"

const uint64_t UnwindMagicValue = 0x12ab34cd;

namespace {

const bool DebugBacktrace = false;

class CodeRecord {
public:
  CodeRecord* next;
  uint64_t begin;
  uint64_t end;
  uint64_t frameSize;
  const char* name;

  // TODO: use something better than linear search
  CodeRecord* find(uint64_t ip) {
    CodeRecord* rec = this;
    while(rec && !(rec->begin <= ip && rec->end > ip)) {
      rec = rec->next;
    }
    return rec;
  }
};

CodeRecord* currentRecords = 0;


/* Parse the debug info off a block of memory, pointed to by MEMORY
   (already copied to GDB's address space) and MEMORY_SZ bytes long.
   The implementation has to use the functions in CB to actually emit
   the parsed data into GDB.  SELF is the same structure returned by
   gdb_init_reader.

   Return GDB_FAIL on failure and GDB_SUCCESS on success.  */

gdb_status readDbgInfo(gdb_reader_funcs *,
                       gdb_symbol_callbacks *cb,
                       void *memory, long memory_sz)
{
  if((unsigned long)memory_sz < 3 * sizeof(uint64_t) + 1) {
    fprintf(stderr, "Avian JIT reader: expected debug info of\n\tstruct{uint64_t begin, uint64_t end, char[] name};\n\tbut found size %ld\n", memory_sz);
    return GDB_FAIL;
  }
  uint64_t* data = static_cast<uint64_t*>(memory);

  uint64_t start = data[0];
  uint64_t length = data[1];
  uint64_t frameSize = data[2];
  const char* name = reinterpret_cast<char*>(&data[3]);

  // TODO: convert endian-ness, if necessary

  if(name[0] != '#') {

    gdb_object* obj = cb->object_open(cb);

    // TODO: get real file info
    gdb_symtab* symtab = cb->symtab_open(cb, obj, "<generated_code>");

    cb->block_open(cb, symtab, 0, start, length, name);

    gdb_line_mapping myLines[] = {
      {1, start},
      {2, start + length}
    };

    cb->line_mapping_add(cb, symtab, 2, myLines);

    cb->symtab_close(cb, symtab);
    cb->object_close(cb, obj);
  }

  CodeRecord* rec = new CodeRecord();
  rec->next = currentRecords;
  rec->begin = start;
  rec->end = start + length;
  rec->frameSize = frameSize;
  rec->name = strdup(name); 

  currentRecords = rec;

  return GDB_SUCCESS;
}

enum DwarfRegisters {
  RIP = 16,
  RBP = 6,
  RSP = 7,
};

bool readRegister(gdb_unwind_callbacks* cb, int dwarfRegister, uint64_t& value, int size) {
  gdb_reg_value* reg = cb->reg_get(cb, dwarfRegister);
  if(reg->size != size || !reg->defined) {
    reg->free(reg);
    return false;
  }
  memcpy(&value, reg->value, size);
  reg->free(reg);
  return true;
}

void myFree(gdb_reg_value* value) {
  free(value);
}

void writeRegister(gdb_unwind_callbacks* cb, int dwarfRegister, uint64_t value, int size) {
  gdb_reg_value* reg = (gdb_reg_value*)malloc(sizeof(gdb_reg_value) + size - 1);
  reg->defined = 1;
  reg->free = myFree;

  memcpy(reg->value, &value, size);
  cb->reg_set(cb, dwarfRegister, reg);
}

bool readMemory(gdb_unwind_callbacks* cb, uint64_t addr, uint64_t& value, int size) {
  value = 0;
  return cb->target_read(addr, &value, size) == GDB_SUCCESS;
}

/* Unwind the current frame, CB is the set of unwind callbacks that
   are to be used to do this.

   Return GDB_FAIL on failure and GDB_SUCCESS on success.  */

gdb_status unwindStack(gdb_reader_funcs *,
                       gdb_unwind_callbacks *cb)
{
  uint64_t ip;
  uint64_t sp;

  if(!readRegister(cb, RIP, ip, 8) || !readRegister(cb, RSP, sp, 8)) {
    if(DebugBacktrace) {
      fprintf(stderr, "fail\n");
    }
    return GDB_FAIL;
  }

  if(DebugBacktrace) {
    fprintf(stderr, "cont 0x%lx\n", ip);
  }

  if(CodeRecord* rec = currentRecords->find(ip)) {
    if(DebugBacktrace) {
      fprintf(stderr, "sp: 0x%lx, ip: 0x%lx framesize: %ld %s\n", sp, ip, rec->frameSize, rec->name);
    }
    if(rec->name[0] == '#') {
      if(DebugBacktrace) {
        fprintf(stderr, "built-in assembly routine %s\n", rec->name + 1);
      }

      const int MaxWordsToSearch = 200;

      for(int i = 0; i < MaxWordsToSearch; i++) {
        uint64_t value;
        uint64_t addr = sp + i * 8;

        if(!readMemory(cb, addr, value, 8)) {
          return GDB_FAIL;
        }
        if(value == UnwindMagicValue) {
          uint64_t oldBp;
          uint64_t oldIp;

          if(!readMemory(cb, addr + 8, oldBp, 8) || !readMemory(cb, addr + 16, oldIp, 8)) {
            return GDB_FAIL;
          }

          writeRegister(cb, RIP, oldIp, 8);
          writeRegister(cb, RSP, addr, 8);
          writeRegister(cb, RBP, oldBp, 8);

          return GDB_SUCCESS;
        }
      }
      return GDB_FAIL;
    } else {
      uint64_t bp = sp + rec->frameSize;

      uint64_t at_bp;
      uint64_t at_bpm1;
      uint64_t at_bpp1;

      if(!readMemory(cb, bp, at_bp, 8) || !readMemory(cb, bp-8, at_bpm1, 8) || !readMemory(cb, bp+8, at_bpp1, 8)) {
        return GDB_FAIL;
      }
      if(DebugBacktrace) {
        fprintf(stderr, "bp: 0x%lx\n", bp);
        fprintf(stderr, "at_bpm1: 0x%lx\n", at_bpm1);
        fprintf(stderr, "at_bp: 0x%lx\n", at_bp);
        fprintf(stderr, "at_bpp1: 0x%lx\n", at_bpp1);
      }

      writeRegister(cb, RIP, at_bp, 8);
      writeRegister(cb, RSP, bp + 8, 8);
      return GDB_SUCCESS;
    }
  } else {
    return GDB_FAIL;
  }
}

/* Return the frame ID corresponding to the current frame, using C to
   read the current register values.  See the comment on struct
   gdb_frame_id.  */

gdb_frame_id getFrameId(gdb_reader_funcs *,
                         gdb_unwind_callbacks *cb)
{
  uint64_t ip;
  uint64_t sp;

  if(!readRegister(cb, RIP, ip, 8) || !readRegister(cb, RSP, sp, 8)) {
    gdb_frame_id ret = {0, 0};
    return ret;
  }

  if(DebugBacktrace) {
    fprintf(stderr, "in getFrameId 0x%lx\n", ip);
  }

  CodeRecord* rec = currentRecords->find(ip);
  gdb_frame_id ret;
  if(rec) {
    ret.code_address = rec->begin;
    ret.stack_address = sp;
  } else {
    fprintf(stderr, "could'nt find frame for 0x%lx\n", ip);
    ret.code_address = 0;
    ret.stack_address = 0;
  }
  return ret;
}

/* Called when a reader is being unloaded.  This function should also
   free SELF, if required.  */

void destroyReader(gdb_reader_funcs *) {
  // do nothing, self is statically allocated (below)
}

} // namespace

static gdb_reader_funcs readerFuncs = {
  /*.reader_version =*/ GDB_READER_INTERFACE_VERSION,
  /*.priv_data =*/ 0,
  /*.read =*/ readDbgInfo,
  /*.unwind =*/ unwindStack,
  /*.get_frame_id =*/ getFrameId,
  /*.destroy =*/ destroyReader
};

extern "C"
gdb_reader_funcs *gdb_init_reader() {
  return &readerFuncs;
}
