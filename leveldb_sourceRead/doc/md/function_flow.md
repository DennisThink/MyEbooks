# 1 DB::Open  
函数原型：

`static Status Open(const Options& options,
                     const std::string& name,
                     DB** dbptr);`


## 1.1 
`DBImpl* impl = new DBImpl(options, dbname);`

## 1.2

`Status s = impl->Recover(&edit, &save_manifest);`

### 1.2.1


## 5.
迭代器，用于访问数据,提供Key，Value，前一个后一个等的访问
```C
class LEVELDB_EXPORT Iterator {
```

### 5.1
DB的迭代器，继承自 迭代器。
```
class DBIter: public Iterator {
```

### 5.2 
迭代器的包装器
class IteratorWrapper {

### 5.3 
Block的迭代器
class Block::Iter : public Iterator {

## 6.
表，是一个string到string的映射关系，通过返回迭代器，被访问
class LEVELDB_EXPORT Table {

## 7.
//用于创建Table
TableBuilder
class LEVELDB_EXPORT TableBuilder {


## 8.
用于创建Block
class BlockBuilder {

放入内存的数据的结构大致如下
// An entry for a particular key-value pair has the form:
//     shared_bytes: varint32
//     unshared_bytes: varint32
//     value_length: varint32
//     key_delta: char[unshared_bytes]
//     value: char[value_length]
// shared_bytes == 0 for restart points.


builder一共有两个，一个blockBuilder，一个tableBuilder，一个FilterBlockBuilder

## 9.Builder
1. ../include/leveldb/table_builder.h
//用于创建Table
class LEVELDB_EXPORT TableBuilder {
  void Add(const Slice& key, const Slice& value);

2. ../table/filter_block.h
class FilterBlockBuilder {
  void AddKey(const Slice& key);

3. ../table/block_builder.h
class BlockBuilder {

  void Add(const Slice& key, const Slice& value);

## 10. handler
../include/leveldb/write_batch.h
Handler
### 10.1 MemTableInserter

../db/write_batch.cc
class MemTableInserter : public WriteBatch::Handler {

### 10.2 WriteBatchItemPrinter

    class WriteBatchItemPrinter : public WriteBatch::Handler {

### 10.3 ../db/db_test.cc
    class Handler : public WriteBatch::Handler {


## 11. SequentialFile

### 11.1 
../helpers/memenv/memenv.cc

class SequentialFileImpl : public SequentialFile {


### 11.2 
../db/log_test.cc
  class StringSource : public SequentialFile {

### 11.3 
../util/env_posix.cc
class PosixSequentialFile final : public SequentialFile {


### 12 FilterPolicy
../include/leveldb/filter_policy.h
提供了默认的bloomFilter

### 13 Comparator
../include/leveldb/comparator.h
提供了基于字典序的默认比较器


文件类型
//文件类型描述
```C
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
```


函数调用流程：
# 1
```C
int main(int argc,char * argv[])
```

## 1.1
```C
Status DB::Open(const Options& options, const std::string& dbname,
                DB** dbptr) 
```

### 1.1.1
call   DBImpl* impl = new DBImpl(options, dbname);
```C
DBImpl::DBImpl(const Options& raw_options, const std::string& dbname)
```
### 1.1.2
call   has_imm_.Release_Store(nullptr);
```C
inline void AtomicPointer::Release_Store(void* v) {
```

### 1.1.3
```C
inline void MemoryBarrier() 
```

### 1.1.4
```C
Status VersionSet::Recover(bool *save_manifest) 
```
### 1.1.5
```cpp
Status ReadFileToString(Env* env, const std::string& fname, std::string* data) {
```

### 1.1.6 
  Builder(VersionSet* vset, Version* base)
## 1.2


class Reader {
## 1.3
	pDB->Put(wtOption,"2","20");
### 1.3.1
Status DBImpl::Put(const WriteOptions& o, const Slice& key, const Slice& val) 
### 1.3.2
Status DB::Put(const WriteOptions& opt, const Slice& key, const Slice& value) 
### 1.3.3
void WriteBatch::Put(const Slice& key, const Slice& value) {
### 1.3.4
Status DBImpl::Write(const WriteOptions& options, WriteBatch* my_batch) {
## 1.4


可以查找的有Version和MemTable
## 2.1
bool MemTable::Get(const LookupKey& key, std::string* value, Status* s) {
## 2.2
inline void SkipList<Key,Comparator>::Iterator::Seek(const Key& target) {
## 2.3
分区间查找
Status Version::Get(const ReadOptions& options,
                    const LookupKey& k,
                    std::string* value,
                    GetStats* stats) {
## 2.4
Status TableCache::Get(const ReadOptions& options,
                       uint64_t file_number,
                       uint64_t file_size,
                       const Slice& k,
                       void* arg,
                       void (*saver)(void*, const Slice&, const Slice&)) {



## Entry格式
    //    klength  varint32
    //    userkey  char[klength]
    //    tag      uint64
    //    vlength  varint32
    //    value    char[vlength]

| ------------------key | value                  |
| --------------------- | ---------------------- |
| klength(varint32)     | userkey(char[klength]) | tag(uint64) | vlength(varint32) | value(char[vlength]) |
**klength = length(userkey)+length(tag)**               


1. TableFile和SSTableFile有什么区别