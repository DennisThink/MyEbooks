// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_DB_BUILDER_H_
#define STORAGE_LEVELDB_DB_BUILDER_H_

#include "leveldb/status.h"

namespace leveldb {

struct Options;
struct FileMetaData;

class Env;
class Iterator;
class TableCache;
class VersionEdit;

// Build a Table file from the contents of *iter.  The generated file
// will be named according to meta->number.  On success, the rest of
// *meta will be filled with metadata about the generated table.
// If no data is present in *iter, meta->file_size will be set to
// zero, and no Table file will be produced.

/**
 * @brief 从迭代器构造一个表，生成的文件名会跟meta—>number相关，如果成功构造，
 *        meta的其他部分都是有关生成的文件的信息，如果iter中没有数据，
 *        meta的file_size字段被置为0，也没有任何表会生成
 * 
 * @param dbname 生成的文件的名字
 * @param env 环境相关的信息
 * @param options 选项
 * @param table_cache  
 * @param iter 迭代器
 * @param meta 文件元数据，作为结果返回
 * @return 成功 Status::OK 失败，其他
 * @caller Status DBImpl::WriteLevel0Table(MemTable* mem, VersionEdit* edit,
                                Version* base)
           Status ConvertLogToTable(uint64_t log) {
    struct LogReporter : public log::Reader::Reporter {
 */
Status BuildTable(const std::string& dbname,
                  Env* env,
                  const Options& options,
                  TableCache* table_cache,
                  Iterator* iter,
                  FileMetaData* meta);

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_DB_BUILDER_H_
