// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_DB_DB_ITER_H_
#define STORAGE_LEVELDB_DB_DB_ITER_H_

#include <stdint.h>
#include "leveldb/db.h"
#include "db/dbformat.h"

namespace leveldb {

class DBImpl;

// Return a new iterator that converts internal keys (yielded by
// "*internal_iter") that were live at the specified "sequence" number
// into appropriate user keys.
/**
 * @brief 返回一个新的迭代器，将internalKey转为userKey
 * @param db 数据库
 * @param user_key_comparator 用户key的比较器
 * @param internal_iter 内部迭代器
 * @param sequence 序列号
 * @param seed 种子
 * @return  UserKey的迭代器
 */

Iterator* NewDBIterator(DBImpl* db,
                        const Comparator* user_key_comparator,
                        Iterator* internal_iter,
                        SequenceNumber sequence,
                        uint32_t seed);

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_DB_DB_ITER_H_
