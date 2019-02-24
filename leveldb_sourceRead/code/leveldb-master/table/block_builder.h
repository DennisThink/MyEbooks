// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_

#include <vector>

#include <stdint.h>
#include "leveldb/slice.h"

namespace leveldb {

struct Options;
/**
 * @class BlockBuilder
 * @author dennis
 * @date 21/11/18
 * @file block_builder.h
 * @brief 用于创建Block
 */

class BlockBuilder {
 public:
  /**
   * @brief 根据Options创建BlockBuilder
   * @param options 创建的选项
   */
  explicit BlockBuilder(const Options* options);

  // Reset the contents as if the BlockBuilder was just constructed.
  /**
   * @brief 重置BlockBuilder
   */
  void Reset();

  // REQUIRES: Finish() has not been called since the last call to Reset().
  // REQUIRES: key is larger than any previously added key
  
  /**
   * @brief 将Key和Value加入到BlockBuilder
   * @param key  key需要保证比之前的key要大
   * @param value
   */
  void Add(const Slice& key, const Slice& value);

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  
  /**
   * @brief 完成创建Block并返回一个Slice指向Block的内容，在调用Reset之前，该Slice有效
   */
  
  Slice Finish();

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  
  /**
   * @brief 返回没有被压缩的当前内容的大小
   */
  size_t CurrentSizeEstimate() const;

  // Return true iff no entries have been added since the last Reset()
  
  /**
   * @brief 判断当前的BlockBuilder是否为空
   * @return 为空返回true，不为空返回false
   */
  bool empty() const {
    return buffer_.empty();
  }

 private:
  const Options*        options_; //保存选项
  std::string           buffer_;      // Destination buffer 实际存放数据的buffer
  std::vector<uint32_t> restarts_;    // Restart points 重新开始的位置数组
  int                   counter_;     // Number of entries emitted since restart 重新开始的个数
  bool                  finished_;    // Has Finish() been called? finish是否已经被调用
  std::string           last_key_;    //最后一个key

  // No copying allowed
  BlockBuilder(const BlockBuilder&);
  void operator=(const BlockBuilder&);
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
