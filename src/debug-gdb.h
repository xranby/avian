/* Copyright (c) 2008-2011, Avian Contributors

   Permission to use, copy, modify, and/or distribute this software
   for any purpose with or without fee is hereby granted, provided
   that the above copyright notice and this permission notice appear
   in all copies.

   There is NO WARRANTY for this software.  See license.txt for
   details. */

#include "common.h"

namespace vm {

class System;

class CompilationHandler {
public:
  virtual void compiled(const void* code, unsigned size, unsigned frameSize, const char* name) = 0;
};

CompilationHandler* makeGdbCompilationHandler(System* s);

}