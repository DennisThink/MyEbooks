// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "util/arena.h"
#include <assert.h>

namespace leveldb {

static const int kBlockSize = 4096;

//构造函数，初始化所有的变量，并不分配开始的内存
Arena::Arena() : memory_usage_(0) {
  alloc_ptr_ = nullptr;  // First allocation will allocate a block
  alloc_bytes_remaining_ = 0;
}

//析构函数，释放所有的内存
Arena::~Arena() {
  for (size_t i = 0; i < blocks_.size(); i++) {
    delete[] blocks_[i];
  }
}

//如果需要的内存数量大于每个块的1/4，则重新分配内存，
//如果小于最大块的1/4，则分配新的内存块(之前剩余的会被浪费掉)，并修改相关的变量
char* Arena::AllocateFallback(size_t bytes) {
  if (bytes > kBlockSize / 4) {
    // Object is more than a quarter of our block size.  Allocate it separately
    // to avoid wasting too much space in leftover bytes.
    char* result = AllocateNewBlock(bytes);
    return result;
  }

  // We waste the remaining space in the current block.
  alloc_ptr_ = AllocateNewBlock(kBlockSize);
  alloc_bytes_remaining_ = kBlockSize;

  char* result = alloc_ptr_;
  alloc_ptr_ += bytes;
  alloc_bytes_remaining_ -= bytes;
  return result;
}

// 按照8字节或者指针大小的字节数对齐分配内存，需要将alloc_ptr_移动到字节对齐处，然后分配，
// 如果剩余的内存不够字节对齐分配，则重新分配新的内存
char* Arena::AllocateAligned(size_t bytes) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  assert((align & (align-1)) == 0);   // Pointer size should be a power of 2
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align-1);
  size_t slop = (current_mod == 0 ? 0 : align - current_mod);
  size_t needed = bytes + slop;
  char* result;
  if (needed <= alloc_bytes_remaining_) {
    result = alloc_ptr_ + slop;
    alloc_ptr_ += needed;
    alloc_bytes_remaining_ -= needed;
  } else {
    // AllocateFallback always returned aligned memory
    result = AllocateFallback(bytes);
  }
  assert((reinterpret_cast<uintptr_t>(result) & (align-1)) == 0);
  return result;
}

// 分配block_bytes字节的内存，并将内存指针记录在blocks_,
// 使用量记录在memory_usage_,然后返回分配的内存
char* Arena::AllocateNewBlock(size_t block_bytes) {
  char* result = new char[block_bytes];
  blocks_.push_back(result);
  memory_usage_.NoBarrier_Store(
      reinterpret_cast<void*>(MemoryUsage() + block_bytes + sizeof(char*)));
  return result;
}

}  // namespace leveldb
