# 1. KeyConvertingIterator
1. 类作用： 将InternalKey转为userKey
2. 所在文件:../table/table_test.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数: 

*重写Seek，将userKey转为interalKey去查找*ggg
```cpp
virtual void Seek(const Slice& target) 
```

*重写key，将internalKey转为UserKey返回*
```cpp
virtual Slice key() const 
```
