# 1. FaultInjectionTest
1. 类作用：  测试数据丢失的时候的情况
2. 所在文件:../db/fault_injection_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
void ReuseLogs(bool reuse)
```

```cpp
void Build(int start_idx, int num_vals)
```

```cpp
Status ReadValue(int i, std::string* val) const
```

```cpp
Status Verify(int start_idx, int num_vals,
                ExpectedVerifResult expected) const 
```
 
```cpp
Slice Key(int i, std::string* storage) const             
```

```cpp
Slice Value(int k, std::string* storage) const 
```

# 2. FaultInjectionTestEnv
1. 类作用：  对Env的函数进行封装，供测试使用
2. 所在文件:../db/fault_injection_test.cc
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:



# 3. FileLock
1. 类作用： 定义一个LockFile
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: PosixFileLock
5. 主要函数:



# 4. FileNameTest
1. 类作用：  对文件名进行测试
2. 所在文件:../db/filename_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 5. FileState
1. 类作用：  引用计数类型，可以完成文件的读取和写入
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*增加引用计数*
```cpp
void Ref()
```
*减少引用计数*
```cpp
void Unref()
```
*获取文件大小*
```cpp
uint64_t Size()
```
*读取数据，将数据放入result中*
```cpp
Status Read(uint64_t offset, size_t n, Slice* result, char* scratch) const
```
*将data添加到FileState中*
```cpp
Status Append(const Slice& data)
```

# 6. FilterBlockBuilder
1. 类作用：  用于对特定的Table创建所有的Filter
2. 所在文件:../table/filter_block.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*调用顺序必须为(StartBlock,若干次AddKey，Finish)*
```cpp
void StartBlock(uint64_t block_offset);
```

```cpp
void AddKey(const Slice& key);
```

```cpp
Slice Finish();
```

# 7. FilterBlockReader
1. 类作用：用给定的FilterPolicy和Slice判断Key是否匹配
2. 所在文件:../table/filter_block.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
*判断Key是否匹配*
```cpp
bool KeyMayMatch(uint64_t block_offset, const Slice& key);
```

# 8. FilterBlockTest
1. 类作用：  对FilterBlockReader和FilterBlockBuilder进行测试
2. 所在文件:../table/filter_block_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 9. FilterPolicy
1. 类作用：  所有Filter的基类
2. 所在文件:../include/leveldb/filter_policy.h
3. 基类: 无
4. 继承类:  BloomFilterPolicy，InternalFilterPolicy，TestHashFilter ，leveldb_filterpolicy_t 
5. 主要函数:

*获取过滤器的名称*
```cpp
virtual const char* Name() const = 0;
```

*创建过滤器，结果保存到dst中*
```cpp
virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const = 0;
```

*判断key是否在filter中*
```cpp
virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const = 0;   
注意KeyMayMatch中的filter与CreateFilter的dst对应。
```

# 10. FindFileTest
1. 类作用： 测试合并
2. 所在文件:../db/version_set_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 11. Footer
1. 类作用：  Footer封装了保存在每个Table文件的末尾的固定信息，主要保存metaindex_handle_和index_handle_
2. 所在文件:../table/format.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
   
*metaindex_handle_的获取和设置函数*
```cpp
const BlockHandle& metaindex_handle() const ;
void set_metaindex_handle(const BlockHandle& h) ;
```

*index_handle_的获取和设置函数*
```cpp
const BlockHandle& index_handle() const ;
void set_index_handle(const BlockHandle& h);
```

*编码Footer内容到dst*
```cpp
void EncodeTo(std::string* dst) const;
```

*从input中解码footer的内容*
```cpp
Status DecodeFrom(Slice* input);
```

# 12. FormatTest
1. 类作用：  对相关的格式进行测试
2. 所在文件:../db/dbformat_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


