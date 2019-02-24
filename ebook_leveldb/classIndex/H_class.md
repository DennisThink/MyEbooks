# 1. HandleTable
1. 类作用：  自己编写的HashTable比默认的速度快
2. 所在文件:../util/cache.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
*根据Key和Hash值查找对应的LRUHandle*
```cpp
LRUHandle* Lookup(const Slice& key, uint32_t hash)
```

*插入LRUHandle*
```cpp
LRUHandle* Insert(LRUHandle* h) 
```

*根据Key和Hash值删除LRUHandle*
```cpp
LRUHandle* Remove(const Slice& key, uint32_t hash) 
```

# 2. Harness
1. 类作用： Constructor的一个封装
2. 所在文件:../table/table_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
void Init(const TestArgs& args) 
void Add(const std::string& key, const std::string& value) 
void TestForwardScan(const std::vector<std::string>& keys,
                       const KVMap& data) 
void TestBackwardScan(const std::vector<std::string>& keys,
                        const KVMap& data)   
void TestRandomAccess(Random* rnd,
                        const std::vector<std::string>& keys,
                        const KVMap& data)                      
```

# 3. HASH
1. 类作用：  对哈希函数进行测试
2. 所在文件:../util/hash_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 4. Histogram
1. 类作用： 柱状统计图
2. 所在文件:../util/histogram.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
void Clear();
void Add(double value);
void Merge(const Histogram& other);

std::string ToString() const;
```
