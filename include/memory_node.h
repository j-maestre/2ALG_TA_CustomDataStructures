/**
 * @file adt_memory_node.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */


#ifndef __MEMORY_NODE_H__
#define __MEMORY_NODE_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

class MemoryNode
{
private:
  MemoryNode();
  MemoryNode(const MemoryNode& other);
  MemoryNode(MemoryNode&& other);

  ~MemoryNode();
  
public:
  MemoryNode& operator=(const MemoryNode& other);
  MemoryNode& operator=(MemoryNode&& other);

  static MemoryNode* Create();
  static s16 CreateFromRef(MemoryNode **node);
  
  void* data();
  s16 setData(void *src, u16 bytes);
  s16 setNext(MemoryNode *next_node);
  s16 setPrevious(MemoryNode *previous_node);
  u16 size();
  s16 reset();
  s16 softReset();
  s16 free();
  s16 softFree();
  s16 memSet(u8 value);
  s16 memCopy(void *src, u16 bytes);
  s16 memConcat(void *src, u16 bytes);
  s16 memMask(u8 mask);
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);
  
  friend class Vector;
  friend class CircularVector;
  friend class MVector;
  friend class List;
  friend class DLList;
  
protected:
  void *data_;
  u16 size_;
  MemoryNode *next_;
  MemoryNode *previous_;
};

#endif //__MEMORY_NODE_H__