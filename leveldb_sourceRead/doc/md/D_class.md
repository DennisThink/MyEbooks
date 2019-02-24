
# 1. DB 
1. 类作用： 数据库的基类和工厂接口类
2. 所在文件:../include/leveldb/db.h
3. 基类: 无
4. 继承类: DBImpl, ModelDB
5. 主要函数:
静态方法，根据option和name构造db，DB结果放在dbptr中返回
static Status Open(const Options& options,
                     const std::string& name,
                     DB** dbptr);

将key和value按照option放入到DB中
virtual Status Put(const WriteOptions& options,
                     const Slice& key,
                     const Slice& value) = 0;

删除对应的key
virtual Status Delete(const WriteOptions& options, const Slice& key) = 0;

将DB中的数据写入WriteBatch
virtual Status Write(const WriteOptions& options, WriteBatch* updates) = 0;

从DB中获取数据
virtual Status Get(const ReadOptions& options,
                     const Slice& key, std::string* value) = 0;

获取DB的迭代器
virtual Iterator* NewIterator(const ReadOptions& options) = 0;

# 1. DBConstructor   
1. 类作用： 对CRC相关函数进行测试
2. 所在文件:../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:

    virtual Status FinishImpl(const Options& options, const KVMap& data) 

     virtual Iterator* NewIterator() const
virtual DB* db() 

# 1. DBImpl   
1. 类作用： DB的一个实现类
2. 所在文件:../db/db_impl.h
3. 基类: DB
4. 继承类: 无
5. 主要函数:
virtual Status Put(const WriteOptions&, const Slice& key, const Slice& value);
virtual Status Delete(const WriteOptions&, const Slice& key);
virtual Status Write(const WriteOptions& options, WriteBatch* updates);
virtual Status Get(const ReadOptions& options,
                    const Slice& key,
                    std::string* value);
virtual Iterator* NewIterator(const ReadOptions&);
virtual const Snapshot* GetSnapshot();
virtual void ReleaseSnapshot(const Snapshot* snapshot);

# 1. DBIter   
1. 类作用： 对CRC相关函数进行测试
2. 所在文件:../util/crc32c_test.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:
迭代器是否有效
 virtual bool Valid() const { return valid_; }
//获取key  
virtual Slice key() const 
获取value
virtual Slice value() const 
获取迭代器的状态
virtual Status status() const 
//移动到下一个
virtual void Next();
//移动到上一个
virtual void Prev();
//移动到指定位置
virtual void Seek(const Slice& target);
//移动到第一个
virtual void SeekToFirst();
//移动到最后一个
virtual void SeekToLast();

# 1. DBTest   
1. 类作用： 对DB进行测试
2. 所在文件:../db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

