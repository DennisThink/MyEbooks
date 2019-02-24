TestWritableFile是对WritableFile的一个包装，当文件被写或同步的时候，可以通知另一个Env。

## 1.构造函数
需要使用WritableFile以及Env构造，说明了其作用。
```cpp
TestWritableFile::TestWritableFile(const FileState& state,
                                   WritableFile* f,
                                   FaultInjectionTestEnv* env)
    : state_(state),
      target_(f),
      writable_file_opened_(true),
      env_(env) {
  assert(f != nullptr);
}
```

## 2.添加内容
调用WritableFile的Append函数，通知Env
```cpp
Status TestWritableFile::Append(const Slice& data) {
  Status s = target_->Append(data);
  if (s.ok() && env_->IsFilesystemActive()) {
    state_.pos_ += data.size();
  }
  return s;
}
```

## 3.缓存同步
```cpp
Status TestWritableFile::Sync() {
  if (!env_->IsFilesystemActive()) {
    return Status::OK();
  }
  // Ensure new files referred to by the manifest are in the filesystem.
  Status s = target_->Sync();
  if (s.ok()) {
    state_.pos_at_last_sync_ = state_.pos_;
  }
  if (env_->IsFileCreatedSinceLastDirSync(state_.filename_)) {
    Status ps = SyncParent();
    if (s.ok() && !ps.ok()) {
      s = ps;
    }
  }
  return s;
}
```