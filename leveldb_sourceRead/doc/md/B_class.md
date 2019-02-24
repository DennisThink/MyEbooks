# 1. Benchmark   
1. 类作用：对数据库进行性能测试
2. 所在文件../db/db_bench.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 2. Block   
1. 类作用：保存一块的数据内容
2. 所在文件../table/block.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

根据BlockContents构造Block
> explicit Block(const BlockContents& contents);

返回Block的大小
> size_t size() const { return size_; }

返回Block对应的迭代器
> Iterator* NewIterator(const Comparator* comparator);


# 3. BlockBuilder   
1. 类作用：用于创建Block
2. 所在文件../table/block_builder.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
构建Block
 explicit BlockBuilder(const Options* options);

重置Block
  void Reset();

将Key和Value加入到blockBuilder
  void Add(const Slice& key, const Slice& value);

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  Slice Finish();

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  size_t CurrentSizeEstimate() const;

  // Return true iff no entries have been added since the last Reset()
  bool empty() const {
    return buffer_.empty();
  }

# 4. BlockConstructor   
1. 类作用：测试中用于构建Block
2. 所在文件../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:
   
根据options和data完成Block的构建
> virtual Status FinishImpl(const Options& options, const KVMap& data) 

返回Block对应的迭代器
> virtual Iterator* NewIterator() const

# 5. BlockHandle   
1. 类作用：完成文件和Block的映射
2. 所在文件../table/format.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

从input中解码出偏移量和文件大小
>Status DecodeFrom(Slice* input);

返回Block在文件中的偏移  
>uint64_t offset() 

返回Block的大小
> uint64_t size() 

设置Block的大小
> void set_size(uint64_t size) 

设置Block在文件中的偏移
>void set_offset(uint64_t offset) 

将偏移量和Block的大小编码到dst中
> void EncodeTo(std::string* dst) const;

# 2. BloomFilterPolicy   
1. 类作用：Bloom过滤器的实现
2. 所在文件../util/bloom.cc
3. 基类: FilterPolicy
4. 继承类: 无
5. 主要函数:

 返回过滤器的名称
>virtual const char* Name() const

根据 n个key构建过滤器，并将结果保存到dst中
> virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const

根据bloom_filter中的数据，判断key是否在其中，
>virtual bool KeyMayMatch(const Slice& key, const Slice& bloom_filter) const 
# 2. BloomTest   
1. 类作用：用作类`BloomFilterPolicy`的自动化测试
2. 所在文件../util/arena_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 2. BloomTest   
1. 类作用：用作类`BloomFilterPolicy`的自动化测试
2. 所在文件../util/bloom_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
6. 