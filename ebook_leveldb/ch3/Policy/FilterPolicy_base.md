FilterPolicy在数据库中查找Key的时候使用，可以减少读取硬盘的次数。

主要函数:

## 1.获取名称
```cpp
virtual const char* Name() const = 0;
```

## 2.根据n个key创建过滤器
```cpp
virtual void CreateFilter(const Slice* keys, int n, std::string* dst)
      const = 0;
```

## 3.判断Key是否在filter中
```cpp
virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const = 0;
```