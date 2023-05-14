#ifndef __VECTOR_H__
#define __VECTOR_H__ 1

/**
 * @file adt_memory_node.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#include "memory_node.h"

class Vector
{
private:
  Vector(u16 size);
  Vector(const Vector& other);
  Vector(Vector&& other);

public:
  ~Vector();
	
  Vector& operator =(const Vector& other);
  Vector& operator =(Vector&& other);

  static Vector* Create(u16 size);

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
	void* extractFirst();
	void* extractLast();
	void* extractAt(u16 position);
	s16 concat(Vector *vector_src);
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

#endif //__VECTOR_H__