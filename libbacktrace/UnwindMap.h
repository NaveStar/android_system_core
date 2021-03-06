/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LIBBACKTRACE_UNWIND_MAP_H
#define _LIBBACKTRACE_UNWIND_MAP_H

#include <backtrace/BacktraceMap.h>

// The unw_map_cursor_t structure is different depending on whether it is
// the local or remote version. In order to get the correct version, include
// libunwind.h first then this header.

class UnwindMap : public BacktraceMap {
public:
  UnwindMap(pid_t pid);
  virtual ~UnwindMap();

  virtual bool Build();

  unw_map_cursor_t* GetMapCursor() { return &map_cursor_; }

protected:
  virtual bool GenerateMap();

  unw_map_cursor_t map_cursor_;
};

class UnwindMapLocal : public UnwindMap {
public:
  UnwindMapLocal();
  virtual ~UnwindMapLocal();

  virtual bool Build();

  virtual const backtrace_map_t* Find(uintptr_t addr);

protected:
  virtual bool GenerateMap();

  bool map_created_;
};

#endif // _LIBBACKTRACE_UNWIND_MAP_H
