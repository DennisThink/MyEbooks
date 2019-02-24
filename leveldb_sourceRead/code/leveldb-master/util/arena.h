// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_UTIL_ARENA_H_
#define STORAGE_LEVELDB_UTIL_ARENA_H_

#include <vector>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include "port/port.h"

namespace leveldb {
//主要的作用是内存分配
class Arena {
 public:
  Arena();
  ~Arena();

  // Return a pointer to a newly allocated memory block of "bytes" bytes.
  // 返回bytes字节的新的内存块
  char* Allocate(size_t bytes);

  // Allocate memory with the normal alignment guarantees provided by malloc
  // 返回具有字节对其的bytes字节的内存块
  char* AllocateAligned(size_t bytes);

  // Returns an estimate of the total memory usage of data allocated
  // by the arena.
  // 返回arena使用的总的内存数量
  size_t MemoryUsage() const {
    return reinterpret_cast<uintptr_t>(memory_usage_.NoBarrier_Load());
  }

 private:

  char* AllocateFallback(size_t bytes);
 
  char* AllocateNewBlock(size_t block_bytes);

  // Allocation state
  // 当前分配的内存的开始位置
  char* alloc_ptr_;
 
  //已经分配的内存的剩余数量 
  size_t alloc_bytes_remaining_;

  // Array of new[] allocated memory blocks
  // 所有分配的内存的vector，在最后释放的时候要用到
  std::vector<char*> blocks_;

  // Total memory usage of the arena.
  // arena的内存使用的总量
  port::AtomicPointer memory_usage_;

  // No copying allowed
  // 禁止拷贝构造函数和拷贝构造运算符
  Arena(const Arena&);
  void operator=(const Arena&);
};

// 分配内存，如果剩余内存足够，则从剩余内存中分配，即if分支
// 否则调用AllocateFallback 进行重新分配
inline char* Arena::Allocate(size_t bytes) {
  // The semantics of what to return are a bit messy if we allow
  // 0-byte allocations, so we disallow them here (we don't need
  // them for our internal use).
  assert(bytes > 0);
  if (bytes <= alloc_bytes_remaining_) {
    char* result = alloc_ptr_;
    alloc_ptr_ += bytes;
    alloc_bytes_remaining_ -= bytes;
    return result;
  }
  return AllocateFallback(bytes);
}

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_UTIL_ARENA_H_
