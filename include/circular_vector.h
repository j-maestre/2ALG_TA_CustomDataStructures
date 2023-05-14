/**
 * @file adt_vector.h
 * @author Jose Maria Maestre <maestrequi@esat-alumni.com>
 */

#ifndef __CIRCULAR_VECTOR_H__
#define __CIRCULAR_VECTOR_H__ 1

#include "memory_node.h"

class CircularVector
{
private:
  CircularVector(u16 size);
  CircularVector(const CircularVector& other);
  CircularVector(CircularVector&& other);

public:
  ~CircularVector();
	
  CircularVector& operator =(const CircularVector& other);
  CircularVector& operator =(CircularVector&& other);

  static CircularVector* Create(u16 size);

  s16 destroy();
  s16 softReset();
  s16 reset();
  s16 resize(u16 new_size);
  u16 capacity() const;
  u16 length() const;
  boolean isEmpty() const;
  boolean isFull() const;
  void* first();
  void* last();
  void* at(u16 position);
  s16 insertFirst(void *data, u16 bytes);
  s16 insertLast(void *data, u16 bytes);
  s16 insertAt(void *data, u16 bytes, u16 position);
  void* extractFirst(u16 *size = nullptr);
  void* extractLast();
  void* extractAt(u16 position);
  s16 concat(CircularVector *vector_src);
  s16 traverse(void (*callback)(MemoryNode *));
  MemoryNode* data();
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);
	
protected:
  u16 head_;
  u16 tail_;
  u16 capacity_;
  MemoryNode *storage_;
};

#endif //__CIRCULAR_VECTOR_H__