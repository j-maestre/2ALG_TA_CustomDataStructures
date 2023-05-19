#ifndef  __DLLIST_H__
#define __DLLIST_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

#include "memory_node.h"

class DLList
{
private:
  DLList(u16 size);
  DLList(const DLList& other) = delete;
  DLList(DLList&& other);

public:
  ~DLList();

  DLList& operator =(const DLList& other) = delete;
  DLList& operator =(DLList&& other);

  static DLList* Create(u16 size);

  s16 destroy();
  s16 softReset();
  s16 reset();
  s16 resize(u16 new_size);
  u16 capacity();
  u16 length();
  boolean isEmpty();
  boolean isFull();
  MemoryNode* first();
  MemoryNode* last();
  MemoryNode* at(u16 position);
  s16 insertFirst(void *data, u16 bytes);
  s16 insertLast(void *data, u16 bytes);
  s16 insertAt(void *data, u16 bytes, u16 position);
  MemoryNode* extractFirst();
  MemoryNode* extractLast();
  MemoryNode* extractAt(u16 position);
  s16 concat(DLList *list_src);
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

#endif //__DLLIST_H__