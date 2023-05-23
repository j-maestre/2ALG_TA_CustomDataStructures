#ifndef __QUEUE_H__
#define __QUEUE_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"
#include "list.h"

class Queue
{
private:
  Queue(u16 size);
  Queue(const Queue& other) = delete;
  Queue(Queue&& other);
  
public:
  ~Queue();

  Queue& operator =(const Queue& other) = delete;
  Queue& operator =(Queue&& other);

  static Queue* Create(u16 size);
  
  s16 reset();
  s16 enqueue(void *data, u16 bytes);
  boolean isEmpty();
  boolean isFull();
  u16 capacity();
  s16 resize(u16 new_size);
  void* dequeue();
  u16 length();
  void* front();
  void* back();
  s16 concat(Queue *queue_src);
  s16 destroy();
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);
  
protected:
  List *storage_;
};

#endif //__QUEUE_H__