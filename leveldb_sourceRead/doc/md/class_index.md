# 1. Cache
leveldb:Cache

主要功能：
插入key和value，
virtual Handle* Insert(const Slice& key, void* value, size_t charge,
                         void (*deleter)(const Slice& key, void* value)) = 0;
查找value
virtual Handle* Lookup(const Slice& key) = 0;