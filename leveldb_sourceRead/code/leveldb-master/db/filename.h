// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// File names used by DB code
// 被dbCode使用到的文件名
#ifndef STORAGE_LEVELDB_DB_FILENAME_H_
#define STORAGE_LEVELDB_DB_FILENAME_H_

#include <stdint.h>
#include <string>
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "port/port.h"

namespace leveldb {

class Env;

//文件类型描述
enum FileType {
  //日志类型
  kLogFile,
  kDBLockFile,
  kTableFile,
  kDescriptorFile,
  kCurrentFile,
  kTempFile,
  kInfoLogFile  // Either the current one, or an old one
};

// Return the name of the log file with the specified number
// in the db named by "dbname".  The result will be prefixed with
// "dbname".
// 根据dbname和number生成log的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	number:2	logName:testdb/000002.log
//      dbname:testFirst	number:123456	logName:testFirst/123456.log
std::string LogFileName(const std::string& dbname, uint64_t number);

// Return the name of the sstable with the specified number
// in the db named by "dbname".  The result will be prefixed with
// "dbname".
// 根据dbname和number生成sstable的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	number:2	logName:testdb/000002.ldb
//      dbname:testFirst	number:123456	logName:testFirst/123456.ldb
std::string TableFileName(const std::string& dbname, uint64_t number);

// Return the legacy file name for an sstable with the specified number
// in the db named by "dbname". The result will be prefixed with
// "dbname".
// 根据dbname和number生成sstable的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	number:2	logName:testdb/000002.ldb
//      dbname:testFirst	number:123456	logName:testFirst/123456.ldb
std::string SSTTableFileName(const std::string& dbname, uint64_t number);

// Return the name of the descriptor file for the db named by
// "dbname" and the specified incarnation number.  The result will be
// prefixed with "dbname".

// 根据dbname和number生成MANIFEST的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	number:2	logName:testdb/MANIFEST-000002
//      dbname:testFirst	number:123456	logName:testFirst/MANIFEST-123456
std::string DescriptorFileName(const std::string& dbname, uint64_t number);

// Return the name of the current file.  This file contains the name
// of the current manifest file.  The result will be prefixed with
// "dbname".
// 根据dbname和number生成CURRENT的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	currentName:testdb/CURRENT
//      dbname:testFirst	logName:testFirst/CURRENT
std::string CurrentFileName(const std::string& dbname);

// Return the name of the lock file for the db named by
// "dbname".  The result will be prefixed with "dbname".
// 根据dbname和number生成LOCK的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	currentName:testdb/LOCK
//      dbname:testFirst	logName:testFirst/LOCK
std::string LockFileName(const std::string& dbname);

// Return the name of a temporary file owned by the db named "dbname".
// The result will be prefixed with "dbname".

// 根据dbname和number生成temp的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	number:2	currentName:testdb/000002.dbtmp
//      dbname:testFirst	number:123456	logName:testFirst/123456.dbtmp
std::string TempFileName(const std::string& dbname, uint64_t number);

// Return the name of the info log file for "dbname".
// 根据dbname和number生成InfoLog的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	infoLogFileName:testdb/LOG
//      dbname:testFirst	infoLogFileName:testFirst/LOG
std::string InfoLogFileName(const std::string& dbname);

// Return the name of the old info log file for "dbname".
// 根据dbname和number生成InfoLog的文件名，文件名以dbname为前缀
// 例：
//      dbname:testdb	infoLogFileName:testdb/LOG.old
//      dbname:testFirst	infoLogFileName:testFirst/LOG.old
std::string OldInfoLogFileName(const std::string& dbname);

// If filename is a leveldb file, store the type of the file in *type.
// The number encoded in the filename is stored in *number.  If the
// filename was successfully parsed, returns true.  Else return false.
// 从filename中解析出number和type，解析成功返回true，解析失败返回false
bool ParseFileName(const std::string& filename,
                   uint64_t* number,
                   FileType* type);

// Make the CURRENT file point to the descriptor file with the
// specified number.
Status SetCurrentFile(Env* env, const std::string& dbname,
                      uint64_t descriptor_number);

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_DB_FILENAME_H_
