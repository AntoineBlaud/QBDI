/*
 * This file is part of QBDI.
 *
 * Copyright 2017 - 2022 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef QBDI_MEMORY_OSTREAM_H
#define QBDI_MEMORY_OSTREAM_H

#include <stddef.h>
#include <stdint.h>

#include "llvm/Support/Memory.h"
#include "llvm/Support/raw_ostream.h"

namespace QBDI {

class memory_ostream : public llvm::raw_ostream {
  llvm::sys::MemoryBlock &os;
  uint64_t pos;

  void write_impl(const char *Ptr, size_t Size) override;

public:
  explicit memory_ostream(llvm::sys::MemoryBlock &O) : os(O) {
    pos = 0;
    SetUnbuffered();
  }
  void seek(uint64_t pos);
  uint64_t current_pos() const override { return pos; }
  void *get_ptr() { return os.base(); }
};

} // namespace QBDI

#endif
