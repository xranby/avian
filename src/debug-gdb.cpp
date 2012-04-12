/* Copyright (c) 2008-2011, Avian Contributors

   Permission to use, copy, modify, and/or distribute this software
   for any purpose with or without fee is hereby granted, provided
   that the above copyright notice and this permission notice appear
   in all copies.

   There is NO WARRANTY for this software.  See license.txt for
   details. */

#include "debug-gdb.h"
#include "system.h"

extern "C" {
  typedef enum
  {
    JIT_NOACTION = 0,
    JIT_REGISTER_FN,
    JIT_UNREGISTER_FN
  } jit_actions_t;

  struct jit_code_entry
  {
    struct jit_code_entry *next_entry;
    struct jit_code_entry *prev_entry;
    const char *symfile_addr;
    uint64_t symfile_size;
  };

  struct jit_descriptor
  {
    uint32_t version;
    /* This type should be jit_actions_t, but we use uint32_t
      to be explicit about the bitwidth.  */
    uint32_t action_flag;
    struct jit_code_entry *relevant_entry;
    struct jit_code_entry *first_entry;
  };

  /* GDB puts a breakpoint in this function.  */
  void __attribute__((noinline)) __jit_debug_register_code() { };

  /* Make sure to specify the version statically, because the
  debugger may check the version before we can set it.  */
  struct jit_descriptor __jit_debug_descriptor = { 1, 0, 0, 0 };
}

namespace {

using namespace vm;

struct SymbolFile {
  uint64_t start;
  uint64_t length;
  uint64_t frameSize;
  char name[1];
};

class MyCompilationHandler: public CompilationHandler {
public:
  MyCompilationHandler(System* s):
    s(s) {}

  virtual void compiled(const void* code, unsigned size, unsigned frameSize, const char* name) {
    // TODO: make thread-safe

    size_t namelen = strlen(name);
    SymbolFile* file = static_cast<SymbolFile*>(allocate(s, sizeof(SymbolFile) + namelen));
    file->start = reinterpret_cast<uint64_t>(code);
    file->length = file->start + size;
    file->frameSize = frameSize;
    strcpy(file->name, name);

    jit_code_entry* entry = static_cast<jit_code_entry*>(allocate(s, sizeof(jit_code_entry)));
    entry->next_entry = __jit_debug_descriptor.first_entry;
    entry->prev_entry = 0;
    entry->symfile_addr = reinterpret_cast<const char*>(file);
    entry->symfile_size = sizeof(SymbolFile) + namelen;

    __jit_debug_descriptor.first_entry = entry;

    __jit_debug_descriptor.relevant_entry = entry;
    __jit_debug_descriptor.action_flag = JIT_REGISTER_FN;
    __jit_debug_register_code();
  }

  // used for locking (eventually...)
  System* s;
};

} // namespace

namespace vm {

CompilationHandler* makeGdbCompilationHandler(System* s) {
  return new (allocate(s, sizeof(MyCompilationHandler))) MyCompilationHandler(s);
}

}