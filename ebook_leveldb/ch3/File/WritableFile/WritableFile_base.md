WritableFile为了序列化的写内容而提供的文件抽象。因为使用者很可能一次性添加很多小段，所以需要提供buffer作为缓存。

## 1.添加内容
```cpp
virtual Status Append(const Slice& data) = 0;
```

## 2.关闭文件
```cpp
  virtual Status Close() = 0;
```

## 3.刷入硬盘
```cpp
 virtual Status Flush() = 0;
```
 
## 4.同步内容
```cpp 
virtual Status Sync() = 0;
```