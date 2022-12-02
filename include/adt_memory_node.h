// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "EDK_MemoryManager/edk_platform_types.h"

// Memory Node type
typedef struct memory_node_s {
  void *data_;
  u16 size_;
  struct memory_node_ops_s *ops_;
} MemoryNode;

// Memory Node's API Declarations
struct memory_node_ops_s {

  /**
   * \brief Get a pointer to the data of the MemoryNode
   * 
   * \param *node pointer to MemorNode
   * 
   * \return void* to the MemoryNode data
   */
  void*(*data) (MemoryNode *node);

  /**
   * \brief Set the data of the MemoryNode
   *        Do not copy
   * 
   * \param *node pointer to MemoryNode
   * \param *src pointer to the allocated block of memory
   * \param u16 bytes size of src
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is zero
   * \return s16 kErrorCode_Null When src is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*setData) (MemoryNode *node, void *src, u16 bytes);

  /**
   * \brief Get the data size of the MemoryNode
   * 
   * \param node pointer to the MemoryNode
   * 
   * \return u16 size of data
   */
  u16(*size) (MemoryNode *node);


  /**
   * \brief Reset the content of the MemoryNode
   *         Freeing only the data
   * 
   * \param node pointer to MemoryNode
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*reset) (MemoryNode *node);

  /**
   * \brief Reset de constent of the MemoryNode
   *        Without freeing the data
   * 
   * \param node poiter to MemoryNode
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*softReset) (MemoryNode *node);
  
  /**
   * \brief Free the data and the MemoryNode
   * 
   * \param node pointer to the MemoryNode
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*free) (MemoryNode *node);

  /**
   * \brief Free only the MemoryNode
   * 
   * \param node pointer to the node 
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has donde his job
   */
  s16(*softFree) (MemoryNode *node);


  /**
   * \brief Set the value in each byte of the data
   * 
   * \param node pointer to the MemoryNode
   * \param value value to be set in the data
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*memSet) (MemoryNode *node, u8 value);

  /**
   * \brief Copy the pointer into the data of the MemoryNode
   * 
   * \param node pointer to the MemoryNode
   * \param src pointer to the data is gonna be copyed
   * \param bytes size of the pointer is gonna be copyed
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_NULL When src is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*memCopy) (MemoryNode *node, void *src, u16 bytes); 

  /**
   * \brief Concat the data of the MemoryNode with the src
   *        Copying the src into a resized data
   * 
   * \param node pointer to the node
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
  s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);
  

  /**
   * \brief Do a mast in each byte of the data of the MemoryNode
   * 
   * \param node pointer to teh MemoryNode
   * \param make masg is gonna be aplyed
   * 
   * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
   * \return s16 kErrorCode_DataNULL When the data of node is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16(*memMask) (MemoryNode *node, u8 mask);

  /**
   * \brief Print the information of the MemoryNode 
   * 
   * \param node pointer to the MemoryNode
   * 
   * \return void
   */
  void(*print) (MemoryNode *node);
};

/**
 * \brief Allocate a new MemoryNode 
 * 
 * \return MemoryNode* pointer to the MemoryNode created
 */
MemoryNode* MEMNODE_create();

/**
 * \brief Create a MemoryNode from reference
 * 
 * \param node pointer to the pointer to the MemoryNode
 * 
 * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
 * \return s16 kErrorCode_Memory When there isn't memory
 * \return s16 kErrorCode_Ok When the function done his job
 */
s16 MEMNODE_createFromRef(MemoryNode **node);

/**
 * \brief Create a new MemoryNode without allocating memory
 * 
 * \param node pointer to the MemoryNode
 * 
 * \return s16 kErrorCode_MemoryNodeNULL When node is NULL
 * \return s16 kErrorCode_Ok When the function has done his job
 */
s16 MEMNODE_createLite(MemoryNode *node);

#endif // __ADT_MEMORY_NODE_H__
