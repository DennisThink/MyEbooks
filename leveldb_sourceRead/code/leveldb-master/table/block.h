// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_TABLE_BLOCK_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_H_

#include <stddef.h>
#include <stdint.h>
#include "leveldb/iterator.h"

namespace leveldb {

struct BlockContents;
class Comparator;

/**
 * @class Block
 * @author dennis
 * @date 21/11/18
 * @file block.h
 * @brief 保存一块的数据内容
 */

class Block {
 public:
  // Initialize the block with the specified contents.
  explicit Block(const BlockContents& contents);

  ~Block();

  
  /**
   * @brief 获取Block的大小
   * @return block的大小
   */
  size_t size() const { return size_; }
  
  /**
   * @brief 根据比较器，返回迭代器
   * @param comparator 比较器
   */
  Iterator* NewIterator(const Comparator* comparator);

 private:
  /**
   * @brief 计算重新开始的Num
   */
  uint32_t NumRestarts() const;

  //保存数据的指针
  const char* data_;
  //block数据的大小
  size_t size_;
  
  //Block的数据中，重新开始的位置
  uint32_t restart_offset_;     // Offset in data_ of restart array
  
  //block持有数据的标识，true为block持有，析构的时候需要删除
  bool owned_;                  // Block owns data_[]

  // No copying allowed
  Block(const Block&);
  void operator=(const Block&);

  class Iter;
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_H_
