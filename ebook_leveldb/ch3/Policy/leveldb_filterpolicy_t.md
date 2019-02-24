leveldb_filterpolicy_t是C语言的接口。用回调函数的方式实现。

## 1.获取过滤器名称
```cpp

  virtual const char* Name() const {
    return (*name_)(state_);
  }
```

## 2.创建过滤器
```cpp
  virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const {
    std::vector<const char*> key_pointers(n);
    std::vector<size_t> key_sizes(n);
    for (int i = 0; i < n; i++) {
      key_pointers[i] = keys[i].data();
      key_sizes[i] = keys[i].size();
    }
    size_t len;
    //调用回调函数实现
    char* filter = (*create_)(state_, &key_pointers[0], &key_sizes[0], n, &len);
    dst->append(filter, len);
    free(filter);
  }
```

## 3.判断Key是不是在filter中
```cpp
  virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const {
    return (*key_match_)(state_, key.data(), key.size(),
                         filter.data(), filter.size());
  }
```