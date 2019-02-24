# 1. InMemoryEnv
1. 类作用： 对Env的内存实现版本
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:


# 2. InternalFilterPolicy
1. 类作用： 过滤器的一个包装，将internalKey转为userKey
2. 所在文件: ../db/dbformat.h
3. 基类:FilterPolicy 
4. 继承类: 无
5. 主要函数:

*获取Filter的名字*
```cpp
virtual const char* Name() const;
```

*根据n个key构造Filter的数据保存到dst中*
```cpp
virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const;
```

*判断key是否在filter中*
```cpp
virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const;
```

# 3. InternalKey 
1. 类作用： 用来封装internalKey防止被误用
2. 所在文件../db/dbformat.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*从Slice中解码*
```cpp
void DecodeFrom(const Slice& s)
```

*返回编码后的内容*
```cpp
Slice Encode() const 
```

*返回user_key*
```cpp
Slice user_key() const
```

*从ParsedInternalKey设置*
```cpp
void SetFrom(const ParsedInternalKey& p) 
```
*清空*
```cpp
void Clear()
```

# 4. InternalKeyComparator 
1. 类作用： InternalKey的比较器
2. 所在文件： ../db/dbformat.h
3. 基类: Comparator 
4. 继承类: 无
5. 主要函数:
参照Comparator的解释

```cpp
virtual const char* Name() const;
virtual int Compare(const Slice& a, const Slice& b) const;
virtual void FindShortestSeparator(
    std::string* start,
    const Slice& limit) const;
virtual void FindShortSuccessor(std::string* key) const;
```

# 5. Issue178 
1. 类作用： 用作测试
2. 所在文件../issues/issue178_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 7. Issue200
1. 类作用： 柱状统计图
2. 所在文件:../issues/issue200_test.**cc**
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 8. Iterator
1. 类作用： 迭代器，用于数据的访问
2. 所在文件:../include/leveldb/iterator.h
3. 基类: 无
4. 继承类: Block::Iter，LevelFileNumIterator，ModelIter 
5. 主要函数:

*迭代器是否有效*
```cpp
virtual bool Valid() const = 0;
```

*移动到起始位置*
```cpp
virtual void SeekToFirst() = 0;
```

*移动到结束位置*
```cpp
virtual void SeekToLast() = 0;
```

*查找对应的target，迭代器移动到对应位置*
```cpp
virtual void Seek(const Slice& target) = 0;
```

*移动到下一个位置*
```cpp
virtual void Next() = 0;
```

*移动到上一个位置*
```cpp
virtual void Prev() = 0;
```

*获取迭代器的Key*
```cpp
virtual Slice key() const = 0;
```

*获取迭代器当前位置的Value*
```cpp
virtual Slice value() const = 0;
```

*获取迭代器的状态*
```cpp
virtual Status status() const = 0;
```

# 9. IteratorWrapper
1. 类作用： 一个内部的迭代器的包装类，提供了与迭代器相同的接口，可以避免虚函数的开销和更好的本地cache
2. 所在文件:../table/iterator_wrapper.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
同Iterator

