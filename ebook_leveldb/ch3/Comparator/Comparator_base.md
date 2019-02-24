Comparator作为左右的比较器的基类，主要定义了四个接口。

## 1. 比较函数
```cpp
virtual int Compare(const Slice& a, const Slice& b) const = 0;
```

## 2.获取比较器的名称
```cpp
virtual const char* Name() const = 0;
```

## 3.获取较短的Key
```cpp
virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const = 0;
```

## 4.获取较短的Successer
```cpp
virtual void FindShortSuccessor(std::string* key) const = 0;
```