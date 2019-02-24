TwoLevelIterator是一个两级的迭代器，第一级为index_iter,第二级为data_iter。

重点函数如下:
## 1.获取状态
```cpp
virtual Status status() const {
    // It'd be nice if status() returned a const Status& instead of a Status
	//如果index_iter的状态不是OK，则返回index_iter的状态
    if (!index_iter_.status().ok()) {
      return index_iter_.status();
	//如果data_iter有效，且状态不是ok,则返回data_iter的状态
    } else if (data_iter_.iter() != nullptr && !data_iter_.status().ok()) {
      return data_iter_.status();
    } else {
	  //返回迭代器的状态
      return status_;
    }
  }
```

## 2.迭代器的移动
先移动index_iter，后移动data_iter_
```cpp
void TwoLevelIterator::SeekToLast() {
  index_iter_.SeekToLast();
  InitDataBlock();
  if (data_iter_.iter() != nullptr) data_iter_.SeekToLast();
  SkipEmptyDataBlocksBackward();
}
```

## 3.与移动有关的两个函数
```cpp
void TwoLevelIterator::InitDataBlock() {
  if (!index_iter_.Valid()) {
    SetDataIterator(nullptr);
  } else {
    Slice handle = index_iter_.value();
    if (data_iter_.iter() != nullptr && handle.compare(data_block_handle_) == 0) {
      // data_iter_ is already constructed with this iterator, so
      // no need to change anything
    } else {
      Iterator* iter = (*block_function_)(arg_, options_, handle);
      data_block_handle_.assign(handle.data(), handle.size());
      SetDataIterator(iter);
    }
  }
}
```

```cpp
void TwoLevelIterator::SkipEmptyDataBlocksBackward() {
  while (data_iter_.iter() == nullptr || !data_iter_.Valid()) {
    // Move to next block
    if (!index_iter_.Valid()) {
      SetDataIterator(nullptr);
      return;
    }
    index_iter_.Prev();
    InitDataBlock();
    if (data_iter_.iter() != nullptr) data_iter_.SeekToLast();
  }
}
```



