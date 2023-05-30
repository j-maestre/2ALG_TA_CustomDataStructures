/**
 * @file memory_node.h
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

/**
 * \brief Allocate a new MemoryNode 
 * 
 * \return MemoryNode* pointer to the MemoryNode created
 */
  static MemoryNode* Create();

/**
 * \brief Create a MemoryNode from reference
 * 
 * \param node pointer to the pointer to the MemoryNode
 * 
 * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
 * \return s16 kErrorCode_Memory When there isn't memory
 * \return s16 kErrorCode_Ok When the function done his job
 */
  static s16 CreateFromRef(MemoryNode **node);
  
  /**
   * \brief Get a pointer to the data of the MemoryNode
   * 
   * \return void* to the MemoryNode data
   */
  void* data();
  
  /**
   * \brief Set the data of the MemoryNode
   *        Do not copy
   * \param *src pointer to the allocated block of memory
   * \param u16 bytes size of src
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is zero
   * \return s16 kErrorCode_Null When src is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 setData(void *src, u16 bytes);
  s16 setNext(MemoryNode *next_node);
  s16 setPrevious(MemoryNode *previous_node);
   
  /**
   * \brief Get the data size of the MemoryNode
   * 
   * \return u16 size of data
   */
  u16 size();
  
  /**
   * \brief Reset the content of the MemoryNode
   *         Freeing only the data
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 reset();
  
  /**
   * \brief Reset de constent of the MemoryNode
   *        Without freeing the data
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 softReset();
    
  /**
   * \brief Free the data and the MemoryNode
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 free();
  
  /**
   * \brief Free only the MemoryNode
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has donde his job
   */
  s16 softFree();
  
  /**
   * \brief Set the value in each byte of the data
   * 
   * \param value value to be set in the data
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 memSet(u8 value);
  
  /**
   * \brief Copy the pointer into the data of the MemoryNode
   * 
   * \param src pointer to the data is gonna be copyed
   * \param bytes size of the pointer is gonna be copyed
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_NULL When src is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 memCopy(void *src, u16 bytes);
  
  /**
   * \brief Concat the data of the MemoryNode with the src
   *        Copying the src into a resized data
   * 
   * \param src pointer to the data is gonna be concated
   * \param bytes size of src
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_NULL When src is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_DataNULL When the data of node is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 memConcat(void *src, u16 bytes);
  
  /**
   * \brief Do a mask in each byte of the data of the MemoryNode
   * 
   * \param make masg is gonna be aplyed
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_DataNULL When the data of node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 memMask(u8 mask);
  
  /**
   * \brief Print the information of the MemoryNode 
   * 
   * \return void
   */
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