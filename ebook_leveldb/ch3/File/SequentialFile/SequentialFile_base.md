SequentialFile是序列化读取文件的抽象接口，主要设计了两个函数,读取函数和跳过函数。

## 1.读取函数
最多读取n个字节的数据，放入到scratch中
```cpp  
virtual Status Read(size_t n, Slice* result, char* scratch) = 0;
```

## 2.跳过若干个字节
```cpp
virtual Status Skip(uint64_t n) = 0;
```