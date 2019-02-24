// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// An iterator yields a sequence of key/value pairs from a source.
// The following class defines the interface.  Multiple implementations
// are provided by this library.  In particular, iterators are provided
// to access the contents of a Table or a DB.
//
// Multiple threads can invoke const methods on an Iterator without
// external synchronization, but if any of the threads may call a
// non-const method, all threads accessing the same Iterator must use
// external synchronization.

#ifndef STORAGE_LEVELDB_INCLUDE_ITERATOR_H_
#define STORAGE_LEVELDB_INCLUDE_ITERATOR_H_

#include "leveldb/export.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

/**
 * @class Iterator
 * @author dennis
 * @date 26/11/18
 * @file iterator.h
 * @brief 迭代器，用于数据的访问
 */
class LEVELDB_EXPORT Iterator {
 public:
  Iterator();

  Iterator(const Iterator&) = delete;
  Iterator& operator=(const Iterator&) = delete;

  virtual ~Iterator();

  // An iterator is either positioned at a key/value pair, or
  // not valid.  This method returns true iff the iterator is valid.
  
  /**
   * @brief 一个迭代器要么是定位到一个key/value的键值对，要么是无效的，
   *        如果迭代器有效(指向键值对),则返回true
   */
  virtual bool Valid() const = 0;

  // Position at the first key in the source.  The iterator is Valid()
  // after this call iff the source is not empty.
  
  /**
   * @brief 定位到源中的第一个key的位置，如果源数据不为空，则此函数调用之后，迭代器有效，Valid()函数返回true
   */
  virtual void SeekToFirst() = 0;

  // Position at the last key in the source.  The iterator is
  // Valid() after this call iff the source is not empty.
  
  /**
   * @brief 定位到源数据的最后一个key的位置，如果源数据不为空，则此函数调用之后，迭代器有效，Valid()函数返回true
   */
  virtual void SeekToLast() = 0;

  // Position at the first key in the source that is at or past target.
  // The iterator is Valid() after this call iff the source contains
  // an entry that comes at or past target.
  
  /**
   * @brief 移动到源数据中的第一个target或者刚过.如果源数据中含有这个target，则迭代器有效
   * @param target 待查找的目标
   */
  virtual void Seek(const Slice& target) = 0;

  // Moves to the next entry in the source.  After this call, Valid() is
  // true iff the iterator was not positioned at the last entry in the source.
  // REQUIRES: Valid()
  
  /**
   * @brief 移动到源数据中的下一个入口，如果迭代器没有定位到最后一个入口，则Valid()返回true。
   *        调用前需要保证Valid()为true
   */
  virtual void Next() = 0;

  // Moves to the previous entry in the source.  After this call, Valid() is
  // true iff the iterator was not positioned at the first entry in source.
  // REQUIRES: Valid()
  /**
   * @brief 移动到源数据中的上一个入口，如果迭代器没有定位到第一个入口，则Valid()返回true。
   *        调用前需要保证Valid()为true
   */
  virtual void Prev() = 0;

  // Return the key for the current entry.  The underlying storage for
  // the returned slice is valid only until the next modification of
  // the iterator.
  // REQUIRES: Valid()
  
  /**
   * @brief 返回当前Entry的Key，在下一次移动迭代器之前，
   */
  virtual Slice key() const = 0;

  // Return the value for the current entry.  The underlying storage for
  // the returned slice is valid only until the next modification of
  // the iterator.
  // REQUIRES: Valid()
  /**
   * @brief 返回当前Entry的Value，迭代器没有移动之前，Slice有效，
   * 		前提：Valid有效
   */
  virtual Slice value() const = 0;

  // If an error has occurred, return it.  Else return an ok status.
  /**
   * @brief 如果发生错误，返回错误的信息，如果没有，返回Status::OK
   */
  virtual Status status() const = 0;

  // Clients are allowed to register function/arg1/arg2 triples that
  // will be invoked when this iterator is destroyed.
  //
  // Note that unlike all of the preceding methods, this method is
  // not abstract and therefore clients should not override it.
  
  using CleanupFunction = void (*)(void* arg1, void* arg2);
  /**
   * @brief 调用者可以注册自己的函数，当此迭代器被销毁的时候，这些注册的函数可以被自动的调用
   * 		此函数不可以被重载
   * @param function 待注册的函数指针
   * @param arg1 参数1，
   * @param arg2 参数2
   */
  void RegisterCleanup(CleanupFunction function, void* arg1, void* arg2);

 private:
  // Cleanup functions are stored in a single-linked list.
  // The list's head node is inlined in the iterator.
  
  /**
   * @class CleanupNode
   * @author dennis
   * @date 27/11/18
   * @file iterator.h
   * @brief 用来保存函数指针的节点，是一个单链表的结构，使用void*作为参数，使其能够接受任何形式的指针
   */
  struct CleanupNode {
    // The head node is used if the function pointer is not null.
    CleanupFunction function;
    void* arg1;
    void* arg2;
    CleanupNode* next;

    // True if the node is not used. Only head nodes might be unused.
    /**
     * @brief 判断当前的函数指针是否为空
     * @return 
     */
    bool IsEmpty() const { return function == nullptr; }
    // Invokes the cleanup function.
	
    /**
     * @brief 调用函数
     */
    void Run() { assert(function != nullptr); (*function)(arg1, arg2); }
  };
  
  CleanupNode cleanup_head_;
};

// Return an empty iterator (yields nothing).

/**
 * @brief 返回一个空的迭代器
 */
LEVELDB_EXPORT Iterator* NewEmptyIterator();

// Return an empty iterator with the specified status.
/**
 * @brief 返回一个状态为status的空迭代器
 * @param status 迭代器的状态
 */
LEVELDB_EXPORT Iterator* NewErrorIterator(const Status& status);

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_INCLUDE_ITERATOR_H_
