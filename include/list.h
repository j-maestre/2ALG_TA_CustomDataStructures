#ifndef __LIST_H__
#define __LIST_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

#include "memory_node.h"

class List
{
private:
  List(u16 size);
  List(const List& other) = delete;
  List(List&& other);

public:
  ~List();

  List& operator =(const List& other) = delete;
  List& operator =(List&& other);

  static List* Create(u16 size);

  s16 destroy();
  s16 softReset();
  s16 reset();
  s16 resize(u16 new_size);
  u16 capacity();
  u16 length();
  boolean isEmpty();
  boolean isFull();
  void* first();
  void* last();
  void* at(u16 position, u16 *size = nullptr);
  s16 insertFirst(void *data, u16 bytes);
  s16 insertLast(void *data, u16 bytes);
  s16 insertAt(void *data, u16 bytes, u16 position);
  void* extractFirst();
  void* extractLast(u16 *size = nullptr);
  void* extractAt(u16 position);
  s16 concat(List *list_src);
  s16 traverse(void (*callback)(MemoryNode *));
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);
  
protected:
  MemoryNode *head_;
  MemoryNode *tail_;
  u16 capacity_;
  u16 lenght_;
};

#endif //__LIST_H__