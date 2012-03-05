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


/* Parse the debug info off a block of memory, pointed to by MEMORY
   (already copied to GDB's address space) and MEMORY_SZ bytes long.
   The implementation has to use the functions in CB to actually emit
   the parsed data into GDB.  SELF is the same structure returned by
   gdb_init_reader.

   Return GDB_FAIL on failure and GDB_SUCCESS on success.  */

gdb_status readDbgInfo(gdb_reader_funcs *self,
                       gdb_symbol_callbacks *cb,
                       void *memory, long memory_sz)
{
  if(memory_sz < 2 * sizeof(uint64_t) + 1) {
    fprintf(stderr, "Avian JIT reader: expected debug info of\n\tstruct{uint64_t begin, uint64_t end, char[] name};\n\tbut found size %d\n", memory_sz);
    return GDB_FAIL;
  }
  uint64_t* data = static_cast<uint64_t*>(memory);

  // TODO: convert endian-ness, if necessary

  gdb_object* obj = cb->object_open(cb);

  // TODO: get real file info
  gdb_symtab* symtab = cb->symtab_open(cb, obj, "<generated_code>");

  fprintf(stderr, "symbol %p %p %s\n", data[0], data[1], reinterpret_cast<char*>(&data[2]));
  gdb_block* block = cb->block_open(cb, symtab, 0, data[0], data[1], reinterpret_cast<char*>(&data[2]));

  cb->symtab_close(cb, symtab);
  cb->object_close(cb, obj);
  return GDB_SUCCESS;
}

/* Unwind the current frame, CB is the set of unwind callbacks that
   are to be used to do this.

   Return GDB_FAIL on failure and GDB_SUCCESS on success.  */

gdb_status unwindStack(gdb_reader_funcs *self,
                       gdb_unwind_callbacks *cb)
{
  return GDB_FAIL;
}

/* Return the frame ID corresponding to the current frame, using C to
   read the current register values.  See the comment on struct
   gdb_frame_id.  */

gdb_frame_id getFrameId(gdb_reader_funcs *self,
                         gdb_unwind_callbacks *c)
{
  // TODO
  gdb_frame_id ret = {
    0,
    0,
  };
  return ret;
}

/* Called when a reader is being unloaded.  This function should also
   free SELF, if required.  */

void destroyReader(gdb_reader_funcs *self) {
  // do nothing, self is statically allocated (below)
}

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
