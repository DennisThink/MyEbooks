InternalFilterPolicy是对FilterPolicy的一个封装，将InternalKey转为UserKey。

## 2.创建过滤器
先将Key转为UserKey，然后再创建过滤器
```cpp
void InternalFilterPolicy::CreateFilter(const Slice* keys, int n,
                                        std::string* dst) const {
  // We rely on the fact that the code in table.cc does not mind us
  // adjusting keys[].
  Slice* mkey = const_cast<Slice*>(keys);
  for (int i = 0; i < n; i++) {
    mkey[i] = ExtractUserKey(keys[i]);
    // TODO(sanjay): Suppress dups?
  }
  user_policy_->CreateFilter(keys, n, dst);
}
```

## 3.判断Key是否在Filter中
先将InternalKey转为UserKey，再判断
```cpp
bool InternalFilterPolicy::KeyMayMatch(const Slice& key, const Slice& f) const {
  return user_policy_->KeyMayMatch(ExtractUserKey(key), f);
}
```