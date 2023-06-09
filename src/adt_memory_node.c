// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node);	// inits a MN with no checks
static void* MEMNODE_data(MemoryNode *node);	// returns a reference to data_
static u16 MEMNODE_size(MemoryNode *node);		// returns data size
static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_reset(MemoryNode *node);
static s16 MEMNODE_softReset(MemoryNode *node);
static s16 MEMNODE_free(MemoryNode *node);
static s16 MEMNODE_softFree(MemoryNode *node);
static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes);
static u16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode *node, u8 mask);
static s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *next_node);
static s16 MEMNODE_setPrevious(MemoryNode *node, MemoryNode *previous_node);
static void MEMNODE_print(MemoryNode *node);


// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops = { .data = MEMNODE_data,
                                             .size = MEMNODE_size,
                                             .setData = MEMNODE_setData,
                                             .reset = MEMNODE_reset,
                                             .softReset = MEMNODE_softReset,
                                             .free = MEMNODE_free,
                                             .softFree = MEMNODE_softFree,
                                             .memSet = MEMNODE_memSet,
                                             .memCopy = MEMNODE_memCopy,
                                             .memConcat = MEMNODE_memConcat,
                                             .memMask = MEMNODE_memMask,
                                             .print = MEMNODE_print,
                                             .setNext = MEMNODE_setNext,
                                             .setPrevious = MEMNODE_setPrevious
};

// Memory Node Definitions
MemoryNode* MEMNODE_create() {
  MemoryNode *node = MM->malloc(sizeof(MemoryNode));
  if (NULL == node) {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_initWithoutCheck(node);
  return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node) {
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
  *node = MEMNODE_create();
  if (NULL == *node) {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  MEMNODE_initWithoutCheck(*node);
  return kErrorCode_Ok;
}

s16 MEMNODE_initWithoutCheck(MemoryNode *node) {
  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;
  node->next_ = NULL;
  node->previous_ = NULL;
  return kErrorCode_Ok;
}

s16 MEMNODE_createLite(MemoryNode *node){
  if( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }

  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;

  return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) { // returns a reference to data_
  if (NULL == node) return NULL;
  return node->data_;
}

u16	MEMNODE_size(MemoryNode *node) { // returns data size
  if (NULL == node) return 0;
  return node->size_;
}

s16 MEMNODE_setData(MemoryNode* node, void* src, u16 bytes) {
  if (NULL == node) {
      return kErrorCode_MemoryNodeNULL;
  }
  if (0 == bytes) {
    return kErrorCode_ZeroBytes;
  }
  
  if (NULL == src) {
    return kErrorCode_NULL;
  }
  
  node->data_ = src;
  node->size_ = bytes;

  return kErrorCode_Ok;
}

s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *next_node)
{
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
  node->next_ = next_node;
  return kErrorCode_Ok;
}

s16 MEMNODE_setPrevious(MemoryNode *node, MemoryNode *prevoius_node)
{
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
  node->previous_ = prevoius_node;
  return kErrorCode_Ok;  
}

s16 MEMNODE_reset(MemoryNode *node) {
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
  if (NULL != node->data_) {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Data freed in the node with location[0x%p] at location 0x%p\n", node, node->data_);
#endif // VERBOSE_
    MM->free(node->data_);
  }

  node->data_ = NULL;
  node->size_ = 0;

  return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode *node) {
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data reseted in the node with location[0x%p] at location 0x%p\n", node, node->data_);
#endif // VERBOSE_

  node->data_ = NULL;
  node->size_ = 0;

  return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode *node) {
  
  if (NULL != node) {

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Freeing data from node[0x%p] with location[0x%p] and size[%d]\n", node, node->data_, node->size_);
#endif
    
    if (NULL != node->data_) {
      MM->free(node->data_);
      node->data_ = NULL;
    }
    MM->free(node);
  }


  return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode* node) {
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Node freed at location[0x%p], without freeing data[0x%p] with size[%d]\n", node, node->data_, node->size_);
#endif
  MM->free(node);

  return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value){
  if ( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }
  u8 *aux = (u8 *) node->data_;

  for(u32 i = 0; i < node->size_; i++){
    aux[i] = value;  
  }
  
  return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes){
  if( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }

  if( NULL == src){
    return kErrorCode_NULL;
  }

  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }
  if (NULL != node->data_) {
    MM->free(node->data_);
  }
  node->data_ = MM->malloc(bytes);

  if( NULL == node->data_){
    return kErrorCode_NoMemory;
  }
  node->size_ = bytes;

  u8 *aux = (u8 *) node->data_;
  u8 *aux2 = (u8 *) src;

  for (u32 i = 0; i < node->size_; i++){
    aux[i] = aux2[i];
  }
  
  return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes){
  if( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }

  if( NULL == src){
    return kErrorCode_NULL;
  }

  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if (NULL == node->data_) {
    return kErrorCode_DataNULL;
  }

  u16 totalBytes = node->size_ + bytes;
  u8 *totalBlock = (u8 *) MM->malloc(totalBytes);
  if (NULL == totalBlock){
    return kErrorCode_NoMemory;
  }
  u8 *aux = (u8 *) node->data_;

  for(u32 i = 0; i < node->size_; i++){
    totalBlock[i] = aux[i];
  }

  aux = (u8 *) src;

  for(u32 i = node->size_; i < totalBytes; i++){
    totalBlock[i] = aux[i-node->size_];
  }

  MM->free(node->data_);
  node->data_ = (void *)totalBlock;
  node->size_ = totalBytes;

  return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode *node, u8 mask){
  if( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }

  if (NULL == node->data_) {
    return kErrorCode_DataNULL;
  }


  u8 *aux = (u8 *) node->data_;

  for (u32 i = 0; i < node->size_; i++){
    aux[i] &= mask;
  }
  
  return kErrorCode_Ok;
}

void MEMNODE_print(MemoryNode *node){
  if( NULL == node){
    return kErrorCode_MemoryNodeNULL;
  }

  printf("[Node Info] Adress: %p\n", node);
  printf("[Node Info] Size: %d\n", node->size_);
  if( NULL != node->data_)printf("[Node Info] Data address: %p\n", node->data_);
  printf("[Node Info] content: ");
  for (u32 i = 0; i < node->size_; i++){
    if (node->data_ != NULL)
    {
      printf("%c",((u8 *) node->data_)[i]);
    }
  }
  printf("\n");

}
