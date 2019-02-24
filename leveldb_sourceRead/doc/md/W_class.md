# 1. WritableFile
1. 类作用： 为了序列化的写内容而提供的文件抽象
2. 所在文件: ../include/leveldb/env.h
3. 基类: 无
4. 继承类: StringDest,DataFile,ManifestFile,PosixWritableFile,StdoutPrinter,StringSink,TestWritableFile
5. 主要函数:
virtual Status Append(const Slice& data) = 0;
virtual Status Close() = 0;
virtual Status Flush() = 0;
virtual Status Sync() = 0;


# 1. WritableFileImpl
1. 类作用： WritableFile的一个实现，数据都保存到了内存中
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: WritableFile
4. 继承类: 无
5. 主要函数:
virtual Status Append(const Slice& data) 
virtual Status Close() { return Status::OK(); }
virtual Status Flush() { return Status::OK(); }
virtual Status Sync() { return Status::OK(); }

# 1. WriteBatch
1. 类作用： 完成批量写
2. 所在文件:../include/leveldb/write_batch.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
放入单个Key和value
  void Put(const Slice& key, const Slice& value);

删除某个key
  void Delete(const Slice& key);

  //将数据放入到handler
  Status Iterate(Handler* handler) const;

# 1. WriteBatchInternal
1. 类作用： 通过静态方法，手动操作WriteBatch
2. 所在文件:../db/write_batch_internal.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 1. WriteBatchItemPrinter
1. 类作用： 实现WriteBatch的Handler，主要目标是写入文件
2. 所在文件: ../db/dumpfile.cc
3. 基类: WriteBatch::Handler
4. 继承类: 无
5. 主要函数:
virtual void Put(const Slice& key, const Slice& value)
virtual void Delete(const Slice& key) 

# 1. WriteBatchTest
1. 类作用： 用来测试WriteBatch
2. 所在文件:../db/write_batch_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 1. Writer
1. 类作用： 用来写日志，与log::Reader对应
2. 所在文件:../db/log_writer.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
Status AddRecord(const Slice& slice);
