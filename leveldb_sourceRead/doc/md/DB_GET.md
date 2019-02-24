# 1. 调用DBImpl::Get
Status DBImpl::Get(const ReadOptions& options,
                   const Slice& key,
                   std::string* value) 
## 1.1 加锁
MutexLock l(&mutex_);
## 1.2 获取SequenceNumber(如果有快照，先从快照获取，否则从VersionSet获取)
if (options.snapshot != nullptr) {
snapshot =
    static_cast<const SnapshotImpl*>(options.snapshot)->sequence_number();
} else {
snapshot = versions_->LastSequence();
}
## 1.3 获取当前Version
Version* current = versions_->current();
## 1.4 低配版智能指针加引用
mem->Ref();
if (imm != nullptr) imm->Ref();
current->Ref();
## 1.5 构造LookupKey
LookupKey lkey(key, snapshot);
## 1.6 在mem中查找
if (mem->Get(lkey, value, &s)) 
### 1.6.1 获取memkey
Slice memkey = key.memtable_key();
### 1.6.2 构造迭代器
Table::Iterator iter(&table_);
### 1.6.3 从迭代器查找(采用二分查找法)
iter.Seek(memkey.data());
### 1.6.4 找到了迭代器，进行精确判断
if (iter.Valid()) {
### 1.6.5 值存在，进行赋值
//值类型，说明数据存在 
    case kTypeValue: {
        Slice v = GetLengthPrefixedSlice(key_ptr + key_length);
        value->assign(v.data(), v.size());
        return true;
    }
### 1.6.7 值不存在
case kTypeDeletion:
    *s = Status::NotFound(Slice());
    return true;

## 1.7 在imm中查找(参考1.6)
imm->Get(lkey, value, &s)

## 1.8 在current中查找
s = current->Get(options, lkey, value, &stats);

### 1.8.1 获取internalKey，userKey以及比较器
Slice ikey = k.internal_key();
Slice user_key = k.user_key();
const Comparator* ucmp = vset_->icmp_.user_comparator();
### 1.8.2 对所有level的数据进行循环
for (int level = 0; level < config::kNumLevels; level++) {
### 1.8.3 在当前level中找出合适的File
先确定文件的范围，比较的是FileMetaData的最大值和最小值
### 1.8.4 在当前文件中查找
 s = vset_->table_cache_->Get(options, f->number, f->file_size,
                                   ikey, &saver, SaveValue);
#### 1.8.4.1
Status s = FindTable(file_number, file_size, &handle);
##### 1.8.4.1.1 根据fileNumber,构造buf
 EncodeFixed64(buf, file_number);
##### 1.8.4.1.2 在Cache中查找key对应的Handle
*handle = cache_->Lookup(key);
##### 1.8.4.1.3 找到了，构造TableFile名，并读取
std::string fname = TableFileName(dbname_, file_number);
RandomAccessFile* file = nullptr;
Table* table = nullptr;
s = env_->NewRandomAccessFile(fname, &file);
##### 1.8.4.1.4 构造SSTable名，并读取
if (!s.ok()) {
    std::string old_fname = SSTTableFileName(dbname_, file_number);
    if (env_->NewRandomAccessFile(old_fname, &file).ok()) {
    s = Status::OK();
    }
}
##### 1.8.4.1.5 打开Table
    if (s.ok()) {
      s = Table::Open(options_, file, file_size, &table);
    }
###### 1.8.4.1.5.1 读取文件末尾信息
Status s = file->Read(size - Footer::kEncodedLength, Footer::kEncodedLength,
                        &footer_input, footer_space);
###### 1.8.4.1.5.2 解析Footer
s = footer.DecodeFrom(&footer_input);
###### 1.8.4.1.5.3 将文件内容读取到index_block_contents中
s = ReadBlock(file, opt, footer.index_handle(), &index_block_contents);
###### 1.8.4.1.5.4 根据读取的数据构造Block以及Table::Rep
Block* index_block = new Block(index_block_contents);
###### 1.8.4.1.5.5 读取元数据
(*table)->ReadMeta(footer);
####### 1.8.4.1.5.5.1 读取block的内容
 if (!ReadBlock(rep_->file, opt, footer.metaindex_handle(), &contents).ok()) {
    // Do not propagate errors since meta info is not needed for operation
    return;
  }
####### 1.8.4.1.5.5.2 构造迭代器
  Iterator* iter = meta->NewIterator(BytewiseComparator());
####### 1.8.4.1.5.5.3 查找filter
  iter->Seek(key);
####### 1.8.4.1.5.5.4 读取过滤器
void Table::ReadFilter(const Slice& filter_handle_value) {



##### 1.8.4.1.6 如果打开成功，就将其加入到Cache，打开失败就返回
if (!s.ok()) {
    assert(table == nullptr);
    delete file;
    // We do not cache error results so that if the error is transient,
    // or somebody repairs the file, we recover automatically.
} else {
    TableAndFile* tf = new TableAndFile;
    tf->file = file;
    tf->table = table;
    *handle = cache_->Insert(key, tf, 1, &DeleteEntry);
}
#### 1.8.4.2
s = t->InternalGet(options, k, arg, saver);
##### 1.8.4.2.1 构造索引值迭代器并查找
  Iterator* iiter = rep_->index_block->NewIterator(rep_->options.comparator);
  iiter->Seek(k);
##### 1.8.4.2.2 如果不在过滤器中，则说明没有
 if (filter != nullptr &&
        handle.DecodeFrom(&handle_value).ok() &&
        !filter->KeyMayMatch(handle.offset(), k)) {
      // Not found
    } else {
##### 1.8.4.2.3 构造新的迭代器，继续查找
      Iterator* block_iter = BlockReader(this, options, iiter->value());
 block_iter->Seek(k);
      if (block_iter->Valid()) {
        (*saver)(arg, block_iter->key(), block_iter->value());
      }
##### 1.8.4.2.1
##### 1.8.4.2.1
##### 1.8.4.2.1


#### 1.8.4.3 释放句柄
cache_->Release(handle);

## 1.9 处理后台任务
if (have_stat_update && current->UpdateStats(stats)) {
MaybeScheduleCompaction();
}
## 1.10 减引用
mem->Unref();
if (imm != nullptr) imm->Unref();
current->Unref();