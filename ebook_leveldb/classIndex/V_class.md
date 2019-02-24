# 1. Version
1. 类作用： 
2. 所在文件:
3. 基类: 无
4. 继承类: 无
5. 主要函数:
**
```cpp
void AddIterators(const ReadOptions&, std::vector<Iterator*>* iters);
```

```cpp
Status Get(const ReadOptions&, const LookupKey& key,          std::string* val,
             GetStats* stats);
```

```cpp
bool RecordReadSample(Slice key);
```

# 2. VersionEdit
1. 类作用： 用来记录Version的变动，包括加入Key,Value,删除key等，并完成编解码
2. 所在文件:../db/version_edit.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
void SetComparatorName(const Slice& name)
```

```cpp
void SetLogNumber(uint64_t num);
```

```cpp
  void SetPrevLogNumber(uint64_t num) {
    has_prev_log_number_ = true;
    prev_log_number_ = num;
  }
  void SetNextFile(uint64_t num) {
    has_next_file_number_ = true;
    next_file_number_ = num;
  }
  void SetLastSequence(SequenceNumber seq) {
    has_last_sequence_ = true;
    last_sequence_ = seq;
  }
  void SetCompactPointer(int level, const InternalKey& key) {
    compact_pointers_.push_back(std::make_pair(level, key));
  }
```

```cpp
  // Add the specified file at the specified number.
  // REQUIRES: This version has not been saved (see VersionSet::SaveTo)
  // REQUIRES: "smallest" and "largest" are smallest and largest keys in file
  void AddFile(int level, uint64_t file,
               uint64_t file_size,
               const InternalKey& smallest,
               const InternalKey& largest) {
    FileMetaData f;
    f.number = file;
    f.file_size = file_size;
    f.smallest = smallest;
    f.largest = largest;
    new_files_.push_back(std::make_pair(level, f));
  }

  // Delete the specified "file" from the specified "level".
  void DeleteFile(int level, uint64_t file) {
    deleted_files_.insert(std::make_pair(level, file));
  }
```

# 3. VersionSet
1. 类作用： Version的双向链表
2. 所在文件:../db/version_set.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
Status LogAndApply(VersionEdit* edit, port::Mutex* mu)
      EXCLUSIVE_LOCKS_REQUIRED(mu);

  // Recover the last saved descriptor from persistent storage.
  Status Recover(bool *save_manifest);

  // Return the current version.
  Version* current() const { return current_; }
```


# 4. VersionEditTest
1. 类作用： 测试VersionEdit
2. 所在文件:../db/version_edit_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数: