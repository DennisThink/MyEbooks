 DataFile根据env的no_space_和data_sync_error_决定添加和同步的操作。
 与[Manifest](./ManifestFile.md)非常的相似。
 ## 1.构造函数
 ```cpp

  DataFile(SpecialEnv* env, WritableFile* base)
      : env_(env),
        base_(base) {
  }
```

## 2.添加内容函数
```cpp
Status Append(const Slice& data) {
  if (env_->no_space_.Acquire_Load() != nullptr) {
    // Drop writes on the floor
    return Status::OK();
  } else {
    return base_->Append(data);
  }
}
```


## 3.同步函数
```cpp
Status Sync() {
  if (env_->data_sync_error_.Acquire_Load() != nullptr) {
    return Status::IOError("simulated data sync error");
  }
  while (env_->delay_data_sync_.Acquire_Load() != nullptr) {
    DelayMilliseconds(100);
  }
  return base_->Sync();
}
```