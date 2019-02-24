// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// A Cache is an interface that maps keys to values.  It has internal
// synchronization and may be safely accessed concurrently from
// multiple threads.  It may automatically evict entries to make room
// for new entries.  Values have a specified charge against the cache
// capacity.  For example, a cache where the values are variable
// length strings, may use the length of the string as the charge for
// the string.
//
// A builtin cache implementation with a least-recently-used eviction
// policy is provided.  Clients may use their own implementations if
// they want something more sophisticated (like scan-resistance, a
// custom eviction policy, variable cache sizing, etc.)

// 缓存是key和value映射的接口，它具有内部的同步功能，所以可以在多线程中安全的调用
// 它可以自动的回收被删除的key和value的空间，用来存放新的key和value。每个值都有一个
// 内部默认实现了 LRU的Cache，用户可以根据自己的情况实现默认的Cache
#ifndef STORAGE_LEVELDB_INCLUDE_CACHE_H_
#define STORAGE_LEVELDB_INCLUDE_CACHE_H_

#include <stdint.h>
#include "leveldb/export.h"
#include "leveldb/slice.h"

namespace leveldb {

class LEVELDB_EXPORT Cache;

// Create a new cache with a fixed size capacity.  This implementation
// of Cache uses a least-recently-used eviction policy.
LEVELDB_EXPORT Cache* NewLRUCache(size_t capacity);

/**
 * @class Cache
 * @author dennis
 * @date 21/11/18
 * @file cache.h
 * @brief key与value的映射接口
 */

class LEVELDB_EXPORT Cache {
 public:
  Cache() = default;

  Cache(const Cache&) = delete;
  Cache& operator=(const Cache&) = delete;

  // Destroys all existing entries by calling the "deleter"
  // function that was passed to the constructor.
  virtual ~Cache();

  // Opaque handle to an entry stored in the cache.
  struct Handle { };

  // Insert a mapping from key->value into the cache and assign it
  // the specified charge against the total cache capacity.
  //
  // Returns a handle that corresponds to the mapping.  The caller
  // must call this->Release(handle) when the returned mapping is no
  // longer needed.
  //
  // When the inserted entry is no longer needed, the key and
  // value will be passed to "deleter".
  
   // TODO:为什么此处的Value是个void*
  /**
   * @brief 将一个Key与Value的映射关系插入到Cache，返回一个与映射一致的句柄，当不在使用这个句柄的时候，调用者必须调用Release函数来释放这个句柄，
   * @param key 待插入的Key
   * @param value 对应的Value
   * @param charge key，value对内存的用量
   * @param deleter 用来删除的回调函数
   * @param key 回调函数的参数key
   * @param value 回调函数的参数value
   * @return 
   */
  virtual Handle* Insert(const Slice& key, void* value, size_t charge,
                         void (*deleter)(const Slice& key, void* value)) = 0;

  // If the cache has no mapping for "key", returns nullptr.
  //
  // Else return a handle that corresponds to the mapping.  The caller
  // must call this->Release(handle) when the returned mapping is no
  // longer needed.
  /**
   * @brief 如果该cache中没有对应的key，返回nullptr，否则返回一个成功的Handle，调用者需要调用Release释放这个Handle
   * @param key 待查找的Key
   */
  
  virtual Handle* Lookup(const Slice& key) = 0;

  // Release a mapping returned by a previous Lookup().
  // REQUIRES: handle must not have been released yet.
  // REQUIRES: handle must have been returned by a method on *this.
  /**
   * @brief 释放LookUp返回的Handle
   * @param handle 
   */
  
  virtual void Release(Handle* handle) = 0;

  // Return the value encapsulated in a handle returned by a
  // successful Lookup().
  // REQUIRES: handle must not have been released yet.
  // REQUIRES: handle must have been returned by a method on *this.
  
  /**
   * @brief 返回Handler对应的值
   * @param handle 由Lookup返回的Handle
   */
  virtual void* Value(Handle* handle) = 0;

  // If the cache contains entry for key, erase it.  Note that the
  // underlying entry will be kept around until all existing handles
  // to it have been released.
  
  /**
   * @brief 如果该Cache中有这个Key，则删除它，(注意：直到跟这个Key有关系的Handle都释放的时候，才真正的删除)
   * @param key 待删除的Key
   */
  virtual void Erase(const Slice& key) = 0;

  // Return a new numeric id.  May be used by multiple clients who are
  // sharing the same cache to partition the key space.  Typically the
  // client will allocate a new id at startup and prepend the id to
  // its cache keys.
  
  /**
   * @brief 在多客户端的情况下使用，防止不同的客户端的Key冲突
   */
  virtual uint64_t NewId() = 0;

  // Remove all cache entries that are not actively in use.  Memory-constrained
  // applications may wish to call this method to reduce memory usage.
  // Default implementation of Prune() does nothing.  Subclasses are strongly
  // encouraged to override the default implementation.  A future release of
  // leveldb may change Prune() to a pure abstract method.
  
  /**
   * @brief 移除不活跃的entries，用于减少内存的占用
   */
  virtual void Prune() {}

  // Return an estimate of the combined charges of all elements stored in the
  // cache.
  virtual size_t TotalCharge() const = 0;

 private:
  void LRU_Remove(Handle* e);
  void LRU_Append(Handle* e);
  void Unref(Handle* e);

  struct Rep;
  Rep* rep_;
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_INCLUDE_CACHE_H_
