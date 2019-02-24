// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "db/builder.h"

#include "db/filename.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "db/version_edit.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"

namespace leveldb {

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
 */
Status BuildTable(const std::string& dbname,
                  Env* env,
                  const Options& options,
                  TableCache* table_cache,
                  Iterator* iter,
                  FileMetaData* meta) {
  Status s;
  meta->file_size = 0;
  //迭代器移动到第一个
  iter->SeekToFirst();

  //根据数据库的名字和meta->number构造文件的名字
  std::string fname = TableFileName(dbname, meta->number);
  //迭代器有效
  if (iter->Valid()) {
    WritableFile* file;
	//根据文件名，创建可写文件
    s = env->NewWritableFile(fname, &file);
    if (!s.ok()) {
      return s;
    }

	//创建TableBuilder
    TableBuilder* builder = new TableBuilder(options, file);
    meta->smallest.DecodeFrom(iter->key());
	//遍历迭代器，将key和value加入builder
    for (; iter->Valid(); iter->Next()) {
      Slice key = iter->key();
      meta->largest.DecodeFrom(key);
      builder->Add(key, iter->value());
    }

    // Finish and check for builder errors
	// Builder 完成
    s = builder->Finish();
    if (s.ok()) {
      meta->file_size = builder->FileSize();
      assert(meta->file_size > 0);
    }
    delete builder;

    // Finish and check for file errors
	// 内容写入文件，并关闭文件
    if (s.ok()) {
      s = file->Sync();
    }
    if (s.ok()) {
      s = file->Close();
    }
    delete file;
    file = nullptr;

	// 检查Table可用
    if (s.ok()) {
      // Verify that the table is usable
      Iterator* it = table_cache->NewIterator(ReadOptions(),
                                              meta->number,
                                              meta->file_size);
      s = it->status();
      delete it;
    }
  }

  // Check for input iterator errors
  // 检查输入迭代器的错误
  if (!iter->status().ok()) {
    s = iter->status();
  }

  if (s.ok() && meta->file_size > 0) {
    // Keep it
  } else {
	//出错的情况下，删除文件
    env->DeleteFile(fname);
  }
  return s;
}

}  // namespace leveldb
