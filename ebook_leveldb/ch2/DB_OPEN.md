# 1 DB::Open 根据选项打开数据库
Status DB::Open(const Options& options, const std::string& dbname,
                DB** dbptr)
## 1.1 创建DBImpl
DBImpl* impl = new DBImpl(options, dbname);

### 1.1.1 规范选项参数
options_(SanitizeOptions(dbname, &internal_comparator_,
                               &internal_filter_policy_, raw_options)),
#### 1.1.1.1 将部分参数限制在选定的范围
ClipToRange(&result.max_open_files,    64 + kNumNonTableCacheFiles, 50000);
ClipToRange(&result.write_buffer_size, 64<<10,                      1<<30);
ClipToRange(&result.max_file_size,     1<<20,                       1<<30);
ClipToRange(&result.block_size,        1<<10,                       4<<20);
#### 1.1.1.2 创建文件文件夹
src.env->CreateDir(dbname);  // In case it does not exist
#### 1.1.1.3 将日志文件重命名为旧的
src.env->RenameFile(InfoLogFileName(dbname), OldInfoLogFileName(dbname));
##### 1.1.1.3.1 生成Info日志文件名
std::string InfoLogFileName(const std::string& dbname);
##### 1.1.1.3.2 生成旧的Info日志文件名
std::string OldInfoLogFileName(const std::string& dbname);

#### 1.1.1.4 创建保存信息的日志文件
Status s = src.env->NewLogger(InfoLogFileName(dbname), &result.info_log);

#### 1.1.1.5 生成LRUCache
result.block_cache = NewLRUCache(8 << 20);

#### 1.1.1.5.1 实际生成SharedLRUCache
return new ShardedLRUCache(capacity);

### 1.1.2 创建TableCache
table_cache_(new TableCache(dbname_, options_, TableCacheSize(options_))),
#### 1.1.2.1 空出10个文件
static int TableCacheSize(const Options& sanitized_options)
#### 1.1.2.2 生成TableCache
TableCache::TableCache(const std::string& dbname,
                       const Options& options,
                       int entries)
##### 1.1.2.2.1 生成LRUCache
Cache* NewLRUCache(size_t capacity) 
###### 1.1.2.2.1 实际生成SharedLRUCache
explicit ShardedLRUCache(size_t capacity)

### 1.1.3 创建WriteBatch
tmp_batch_(new WriteBatch)
#### 1.1.3.1 清空WriteBatch中的rep_中的数据
void WriteBatch::Clear()

### 1.1.4 创建VersionSet
versions_(new VersionSet(dbname_, &options_, table_cache_,
                               &internal_comparator_)) 

#### 1.1.4.1 创建Version，并添加到VersionSet中(在带有头结点的双向链表中加入一个节点)
AppendVersion(new Version(this));
##### 1.1.4.1.1 创建Version
new Version(this)
### 1.1.5
has_imm_.Release_Store(nullptr);


## 1.2 mutex加锁
impl->mutex_.Lock();

## 1.3 从文件中恢复数据
Status s = impl->Recover(&edit, &save_manifest);
```
Status DBImpl::Recover(VersionEdit* edit, bool *save_manifest)
```
### 1.3.1 持有锁的判断
mutex_.AssertHeld();
### 1.3.2 创建目录
env_->CreateDir(dbname_);
### 1.3.3 文件加锁
Status s = env_->LockFile(LockFileName(dbname_), &db_lock_);
### 1.3.4 判断文件是否存在
env_->FileExists(CurrentFileName(dbname_)）
#### 1.3.4.1 生成CURRENT文件的文件名
CurrentFileName(dbname_)
### 1.3.5 没有旧的DB,首次创建
s = NewDB();
#### 1.3.5.1 设置VersionEdit的一些属性
new_db.SetComparatorName(user_comparator()->Name());
//日志文件为0，DescriptorFile为1
new_db.SetLogNumber(0);
//下一个文件为2
new_db.SetNextFile(2);
//起始序列号为0
new_db.SetLastSequence(0);
// 生成Manifest的文件名
const std::string manifest = DescriptorFileName(dbname_, 1);
#### 1.3.5.2 创建可写文件
Status s = env_->NewWritableFile(manifest, &file);
#### 1.3.5.3 用File构造Writer
log::Writer log(file);
#### 1.3.5.1 将VersionEdit的数据保存到dst中
new_db.EncodeTo(&record);
#### 1.3.5.1 将内容保存到log::Writer
s = log.AddRecord(record);
#### 1.3.5.1 将内容保存到log::Writer
s = file->Close();
#### 1.3.5.1 成功的情况下将dbname和descriptor_number的文件名设置为当前数据库的名称
s = SetCurrentFile(env_, dbname_, 1);
#### 1.3.5.1 失败的情况下，删除文件
env_->DeleteFile(manifest);

### 1.3.6 VersionSet的Recover
s = versions_->Recover(save_manifest);
#### 1.3.6.1 读取保存了当前Manifest的“CURRENT"文件
Status s = ReadFileToString(env_, CurrentFileName(dbname_), &current);
##### 1.3.6.1.1 返回"CURRENT"的名字
CurrentFileName(dbname_)
##### 1.3.6.1.2 根据文件名称，创建一个序列化读取的类
Status s = env->NewSequentialFile(fname, &file);
##### 1.3.6.1.3 从文件中读取数据
s = file->Read(kBufferSize, &fragment, space);
##### 1.3.6.1.4 将数据放入结果中
data->append(fragment.data(), fragment.size());

#### 1.3.6.2 创建针对CURRENT的读取类
s = env_->NewSequentialFile(dscname, &file);
#### 1.3.6.3 创建日志读取类
 log::Reader reader(file, &reporter, true/*checksum*/, 0/*initial_offset*/);
#### 1.3.6.4 循环读取记录
while (reader.ReadRecord(&record, &scratch) && s.ok()) {
##### 1.3.6.4.1 跳过初始化块
if (!SkipToInitialBlock()) 
###### 1.3.6.4.1.1 跳过block_start_location
Status skip_status = file_->Skip(block_start_location);
##### 1.3.6.4.1 将读好的数据放入到fragment中(最多两次读完了，待验证TODO)
const unsigned int record_type = ReadPhysicalRecord(&fragment);
数据格式如下:
```
|---4byte---|--2byte---|1byte |(datalen-7)|
|-----CRC---|--datalen-| type |data_part  |
CRC = crc32(data_part)
```
###### 1.3.6.4.1.2 检查校验和
uint32_t expected_crc = crc32c::Unmask(DecodeFixed32(header));
uint32_t actual_crc = crc32c::Value(header + 6, 1 + length);
##### 1.3.6.4.5 读取数据出错，报错
ReportCorruption(scratch->size(), "partial record without end(1)");

#### 1.3.6.5 解析读取的数据
s = edit.DecodeFrom(record);

> 与void VersionEdit::EncodeTo(std::string* dst) const 对应

##### 1.3.6.5.1 清空之前的记录
Status VersionEdit::Clear()
##### 1.3.6.5.2 按字段解析记录
1. 获取比较器的名称
case kComparator:
2. 获取LogNumber
case kLogNumber:   
3. 获取PrevLogNumber
case kPrevLogNumber:
4. 获取NextFileNumber
case kNextFileNumber:
5. 获取LastSequence
case kLastSequence:
6. 获取CompactPointer.
case kCompactPointer:
7. 获取DeletedFile
case kDeletedFile:
2. 获取NewFile
case kNewFile:
#### 1.3.6.6 比较比较器的名字
edit.comparator_ != icmp_.user_comparator()->Name()) {
#### 1.3.6.7 将Edit应用到Builder
builder.Apply(&edit)
1. 更新Compaction的指针
2. 删除文件
3. 添加新的文件
FileMetaData* f = new FileMetaData(edit->new_files_[i].second);
#### 1.3.6.8 更新最大文件计数
MarkFileNumberUsed(prev_log_number);
MarkFileNumberUsed(log_number);
#### 1.3.6.9 从VersionSet构建Version
Version* v = new Version(this);
#### 1.3.6.10 将当前状态保存到Version
builder.SaveTo(v);
##### 1.3.6.10.1 将base_iter的内容保存到v的files中
MaybeAddFile(v, level, *base_iter);
#### 1.3.6.11 计算best_level和best_score并保存到v中
Finalize(v);
#### 1.3.6.12 将v加入到VersionSet中
AppendVersion(v); 
#### 1.3.6.13 重用manifest
if (ReuseManifest(dscname, current)) 
##### 1.3.6.13.1 解析文件名，获取数字和描述
ParseFileName(dscbase, &manifest_number, &manifest_type)
##### 1.3.6.13.2 将旧的manifest文件赋值给descriptor_file
Status r = env_->NewAppendableFile(dscname, &descriptor_file_);
##### 1.3.6.13.3 用descriptor_file_构建descriptor_log
descriptor_log_ = new log::Writer(descriptor_file_, manifest_size);

### 1.3.7 获取当前使用的log和前一个log的编号
const uint64_t min_log = versions_->LogNumber();
const uint64_t prev_log = versions_->PrevLogNumber();

### 1.3.8 获取 dbname_下的文件的名字
s = env_->GetChildren(dbname_, &filenames);

### 1.3.9 将当前使用的编号加入到expected
versions_->AddLiveFiles(&expected);

### 1.3.10 解析文件名获取类型和编号
if (ParseFileName(filenames[i], &number, &type)) {
### 1.3.11 从日志文件恢复
s = RecoverLogFile(logs[i], (i == logs.size() - 1), save_manifest, edit,
                       &max_sequence);
#### 1.3.11.1 获取日志的文件名，并且打开文件
std::string fname = LogFileName(dbname_, log_number);
Status status = env_->NewSequentialFile(fname, &file);
#### 1.3.11.2 根据文件构建Reader
log::Reader reader(file, &reporter, true/*checksum*/,
                     0/*initial_offset*/);
#### 1.3.11.2 读取记录
while (reader.ReadRecord(&record, &scratch) &&
#### 1.3.11.2 将record设置到batch中
WriteBatchInternal::SetContents(&batch, record);
#### 1.3.11.2 创建MemTable
mem = new MemTable(internal_comparator_);
#### 1.3.11.2 将Mem挂载到batch中
status = WriteBatchInternal::InsertInto(&batch, mem);
#### 1.3.11.8
if (mem->ApproximateMemoryUsage() > options_.write_buffer_size) {
Status DBImpl::WriteLevel0Table(MemTable* mem, VersionEdit* edit,
                                Version* base) {
##### 1.3.11.8.1 从迭代器构造一个表，生成的文件名会跟meta—>number相关
s = BuildTable(dbname_, env_, options_, table_cache_, iter, &meta);
##### 1.3.11.8.1 选出MemTableOutput的最大level
level = base->PickLevelForMemTableOutput(min_user_key, max_user_key);
##### 1.3.11.8.1 将feil和level的对应关系记录下来
edit->AddFile(level, meta.number, meta.file_size,
                  meta.smallest, meta.largest);

#### 1.3.11.9 是否重用最后的日志文件
// See if we should keep reusing the last log file.
#### 1.3.11.10 不再重用日志文件，将文件写入到
status = WriteLevel0Table(mem, edit, nullptr);

### 1.3.12 设置被使用的文件以及最大序列号
versions_->MarkFileNumberUsed(logs[i]);
versions_->SetLastSequence(max_sequence);

## 1.4 获取新的日志编号
uint64_t new_log_number = impl->versions_->NewFileNumber();
## 1.5 根据日志编号生成新的日志文件
s = options.env->NewWritableFile(LogFileName(dbname, new_log_number),
                                     &lfile);
## 1.6 设置日志编号
edit.SetLogNumber(new_log_number);
## 1.7 设置日志文件
impl->log_ = new log::Writer(lfile);
## 1.8 生成新的MemTable
impl->mem_ = new MemTable(impl->internal_comparator_);
## 1.9 MemTable加引用
impl->mem_->Ref();

## 1.10 设置上一个日志的编号
edit.SetPrevLogNumber(0);  // No older logs needed after recovery.
## 1.11 设置LogNumber
edit.SetLogNumber(impl->logfile_number_);
## 1.12 记录日志，应用VersionEdit
s = impl->versions_->LogAndApply(&edit, &impl->mutex_);
### 1.12.1 给VersionEdit设置相关属性
### 1.12.2 构造Version，并且保存
  Version* v = new Version(this);
  {
    Builder builder(this, current_);
    builder.Apply(edit);
    builder.SaveTo(v);
  }
  Finalize(v);
### 1.12.3 构造新的Manifest
### 1.12.4 将新的记录写入到Manifest
### 1.12.5 安装新的Version
 // Install the new version


## 1.13 删除不用的文件
impl->DeleteObsoleteFiles();

## 1.14 安排后台的进程
impl->MaybeScheduleCompaction();
## 1.15 解锁
impl->mutex_.Unlock();

