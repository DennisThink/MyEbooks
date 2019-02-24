# 1. DB::Put
Status DB::Put(const WriteOptions& opt, const Slice& key, const Slice& value) 
## 1.1 写入WriteBatch
batch.Put(key, value);
### 1.1.1 设置Count
WriteBatchInternal::SetCount(this, WriteBatchInternal::Count(this) + 1);
### 1.1.2 写入具体数据
// 放入数据类型
rep_.push_back(static_cast<char>(kTypeValue));
// 放入Key
PutLengthPrefixedSlice(&rep_, key);、
// 放入Value
PutLengthPrefixedSlice(&rep_, value);
## 1.2
return Write(opt, &batch);
### 1.2.1 进行同步
Writer w(&mutex_);
w.batch = my_batch;
w.sync = options.sync;
w.done = false;

MutexLock l(&mutex_);
writers_.push_back(&w);
while (!w.done && &w != writers_.front()) {
w.cv.Wait();
}
if (w.done) {
return w.status;
}
### 1.2.2 构建Mem_以及log_
Status status = MakeRoomForWrite(my_batch == nullptr);
#### 1.2.2.1 处理后台任务
#### 1.2.2.2　创建LogFile以MemTable
      // Attempt to switch to a new memtable and trigger compaction of old
      assert(versions_->PrevLogNumber() == 0);
      uint64_t new_log_number = versions_->NewFileNumber();
      WritableFile* lfile = nullptr;
      s = env_->NewWritableFile(LogFileName(dbname_, new_log_number), &lfile);
      if (!s.ok()) {
        // Avoid chewing through file number space in a tight loop.
        versions_->ReuseFileNumber(new_log_number);
        break;
      }
      delete log_;
      delete logfile_;
      logfile_ = lfile;
      logfile_number_ = new_log_number;
      log_ = new log::Writer(lfile);
      imm_ = mem_;
      has_imm_.Release_Store(imm_);
      mem_ = new MemTable(internal_comparator_);
      mem_->Ref();
      force = false;   // Do not force another compaction if have room
      MaybeScheduleCompaction();
### 1.2.3 获取序列号
 uint64_t last_sequence = versions_->LastSequence();
### 1.2.4 将Writer中的Batch做拼接，并返回拼接后的结果
    WriteBatch* updates = BuildBatchGroup(&last_writer);
### 1.2.5 设置序列号
    WriteBatchInternal::SetSequence(updates, last_sequence + 1);
### 1.2.6 计算个数
    last_sequence += WriteBatchInternal::Count(updates);

### 1.2.7 将update的内容写入log_
     status = log_->AddRecord(WriteBatchInternal::Contents(updates));
#### 1.2.7.1 写入7字节的开始头
dest_->Append(Slice("\x00\x00\x00\x00\x00\x00", leftover));
#### 1.2.7.2 将ptr所指向的内容，加入到dest_
 s = EmitPhysicalRecord(type, ptr, fragment_length);
### 1.2.8 将数据从Updates放入mem_
status = WriteBatchInternal::InsertInto(updates, mem_);
###　1.2.9 记录下后台运行的错误消息
  RecordBackgroundError(status);
### 1.2.10 同步
  while (true) {
    Writer* ready = writers_.front();
    writers_.pop_front();
    if (ready != &w) {
      ready->status = status;
      ready->done = true;
      ready->cv.Signal();
    }
    if (ready == last_writer) break;
  }

  // Notify new head of write queue
  if (!writers_.empty()) {
    writers_.front()->cv.Signal();
  }
