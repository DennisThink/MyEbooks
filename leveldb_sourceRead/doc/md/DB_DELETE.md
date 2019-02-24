# 1. 数据库删除
Status DB::Delete(const WriteOptions& opt, const Slice& key) 
## 1.1
batch.Delete(key);
###
  WriteBatchInternal::SetCount(this, WriteBatchInternal::Count(this) + 1);
  rep_.push_back(static_cast<char>(kTypeDeletion));
  PutLengthPrefixedSlice(&rep_, key);
## 1.2
return Write(opt, &batch);