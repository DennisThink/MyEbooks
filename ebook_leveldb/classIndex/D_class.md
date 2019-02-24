
# 1. DB 
1. 类作用： 数据库的基类和工厂接口类
2. 所在文件:../include/leveldb/db.h
3. 基类: 无
4. 继承类: DBImpl, ModelDB
5. 主要函数:

*静态方法，根据option和name构造db，DB结果放在dbptr中返回*
```cpp
static Status Open(const Options& options,
                     const std::string& name,
                     DB** dbptr);
```

*将key和value按照option放入到DB中*
```cpp
virtual Status Put(const WriteOptions& options,
                     const Slice& key,
                     const Slice& value) = 0;
```

*删除对应的key*
```cpp
virtual Status Delete(const WriteOptions& options, const Slice& key) = 0;
```

*将DB中的数据写入WriteBatch*
```cpp
virtual Status Write(const WriteOptions& options, WriteBatch* updates) = 0;
```

*从DB中获取数据*
```cpp
virtual Status Get(const ReadOptions& options,
                     const Slice& key, std::string* value) = 0;
```

*获取DB的迭代器*
```cpp
virtual Iterator* NewIterator(const ReadOptions& options) = 0;
```

# 2. DBConstructor   
1. 类作用： DB的构造器，继承自Constructor
2. 所在文件:../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:

*根据选项和数据生成DB*
```cpp
virtual Status FinishImpl(const Options& options, const KVMap& data);
```
*返回DB的迭代器*
```cpp
virtual Iterator* NewIterator() const
```

*返回创建好的DB*
```cpp
virtual DB* db() 
```

# 3. DBImpl   
1. 类作用： DB的一个实现类
2. 所在文件:../db/db_impl.h
3. 基类: DB
4. 继承类: 无
5. 主要函数:

*将key和value按照option放入到DB中*
```cpp
virtual Status Put(const WriteOptions& options,
                     const Slice& key,
                     const Slice& value) = 0;
```

*删除对应的key*
```cpp
virtual Status Delete(const WriteOptions& options, const Slice& key) = 0;
```

*将DB中的数据写入WriteBatch*
```cpp
virtual Status Write(const WriteOptions& options, WriteBatch* updates) = 0;
```

*从DB中获取数据*
```cpp
virtual Status Get(const ReadOptions& options,
                     const Slice& key, std::string* value) = 0;
```

*获取DB的迭代器*
```cpp
virtual Iterator* NewIterator(const ReadOptions& options) = 0;
```

*获取快照*
```cpp
virtual const Snapshot* GetSnapshot();
```

*释放快照*
```cpp
virtual void ReleaseSnapshot(const Snapshot* snapshot);
```

# 4. DBIter   
1. 类作用： DB的Iterator的实现
2. 所在文件:../db/db_iter.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:

*迭代器是否有效*
```cpp
virtual bool Valid() const;
```
*获取key*
```cpp  
virtual Slice key() const 
```

*获取value*
```cpp
virtual Slice value() const 
```

*获取迭代器的状态*
```cpp
virtual Status status() const 
```
*移动到下一个*
```cpp
virtual void Next();
```
*移动到上一个*
```cpp
virtual void Prev();
```

*移动到指定位置*
```cpp
virtual void Seek(const Slice& target);
```
*移动到第一个*
```cpp
virtual void SeekToFirst();
```

*移动到最后一个*
```cpp
virtual void SeekToLast();
```

# 5. DBTest   
1. 类作用： 对DB进行测试
2. 所在文件:../db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 6.DataFile
1. 类作用： 根据同步标志来操作Append和Sync
2. 所在文件:../db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 6.ManifestFile
1. 类作用： 根据同步标志来操作Append和Sync
2. 所在文件:../db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数: