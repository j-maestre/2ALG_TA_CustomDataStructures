#include <stdio.h>

#include "adt_list.h"
#include "common_def.h"
#include "EDK_MemoryManager/edk_memory_manager.h"


static s16 List_destroy(List *list);
static s16 List_softReset(List *list);
static s16 List_reset(List *list);
static s16 List_resize(List *list, u16 new_size);
static u16 List_capacity(List *list);
static u16 List_lenght(List *list);
static boolean List_isEmpty(List *list);
static boolean List_isFull(List *list);
static void* List_first(List *list);
static void* List_last(List *list);
static void* List_at(List *list, u16 position);
static s16 List_insertFirst(List *list, void *data, u16 bytes);
static s16 List_insertLast(List *list, void *data, u16 bytes);
static s16 List_insertAt(List *list, void *data, u16 bytes, u16 position);
static void* List_extractFirst(List *list);
static void* List_extractLast(List *list);
static void* List_extractAt(List *list, u16 position);
static s16 List_concat(List *list, List *List_src);
static s16 List_traverse(List *list, void (*callback)(MemoryNode *));
static void List_print(List *list);
static void List_initWithoutCheck(List *list);
static MemoryNode *List_extractLastInternal(List *list);

struct list_ops_s list_ops = { .destroy = List_destroy,
                                   .softReset = List_softReset,
                                   .reset = List_reset,
                                   .resize = List_resize,
                                   .capacity = List_capacity,
                                   .length = List_lenght,
                                   .isEmpty = List_isEmpty,
                                   .isFull = List_isFull,
                                   .first = List_first,
                                   .last = List_last,
                                   .at = List_at,
                                   .insertFirst = List_insertFirst,
                                   .insertLast = List_insertLast,
                                   .insertAt = List_insertAt,
                                   .extractFirst = List_extractFirst,
                                   .extractLast = List_extractLast,
                                   .extractAt = List_extractAt,
                                   .concat = List_concat,
                                   .traverse = List_traverse,
                                   .print = List_print                   
                                   };

List* List_create(u16 capacity) {
  if (capacity == 0)
    return NULL;

  List *list = (List *)MM->malloc(sizeof(List));
  if (list == NULL)
    return NULL;

  List_initWithoutCheck(list);

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("List has been created with location[0x%p] and capacity[%d]\n", list, capacity);
#endif
  
  list->capacity_ = capacity;
  
	return list;
}

void List_initWithoutCheck(List *list)
{
  list->capacity_ = 0;
  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  list->ops_ = &list_ops;
}

s16 List_destroy(List *list){ 
  if (list == NULL)
    return kErrorCode_NULL;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Destroying list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif
  
  MemoryNode *current = list->head_;
  MemoryNode *next = list->head_->next_;

  while (current != NULL)
  {
    current->ops_->free(current);
    current = next;
    next = next->next_;
  }

  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  
  return kErrorCode_Ok;
}

s16 List_softReset(List *list){ 
  if (list == NULL)
    return kErrorCode_NULL;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Soft resetting list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif
  
  MemoryNode *current = list->head_;
  MemoryNode *next = list->head_->next_;

  while (current != NULL)
  {
    current->ops_->softFree(current);
    current = next;
    next = next->next_;
  }

  list->lenght_ = 0;
  
  return kErrorCode_Ok;
}

s16 List_reset(List *list){
  if (list == NULL)
    return kErrorCode_NULL;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Resetting list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif
  
  MemoryNode *current = list->head_;
  MemoryNode *next = list->head_->next_;

  while (current != NULL)
  {
    current->ops_->softFree(current);
    current = next;
    next = next->next_;
  }

  list->lenght_ = 0;
  
  return kErrorCode_Ok;
}

s16 List_resize(List *list, u16 new_size){ 
  if (list == NULL)
   return kErrorCode_NULL;

  MemoryNode *current = NULL;
  while (list->lenght_ > new_size)
  {
    current = List_extractLastInternal(list);
    current->ops_->free(current);
  }

  list->capacity_ = new_size;
  
  return kErrorCode_Ok;
}

u16 List_capacity(List *list){
  if (list == NULL)
    return 0;
  return list->capacity_;
}

u16 List_lenght(List *list){
  if (list == NULL)
    return 0;
  return list->lenght_;

}

boolean List_isEmpty(List *list){
  if (list == NULL)
    return False;
  return (list->lenght_ == 0);
}

boolean List_isFull(List *list){
  if (list == NULL)
    return True;
  return (list->lenght_ == list->capacity_);
}

void* List_first(List *list){
  if (list == NULL)
    return NULL;
  
  return list->head_;
}

void* List_last(List *list){
  if (list == NULL)
    return NULL;
  
  return list->tail_;
} 

void* List_at(List *list, u16 position){
  if (list == NULL)
    return NULL;

  MemoryNode *current = list->head_;

  if (position > list->lenght_)
    position = list->lenght_;
  
  for (u16 i = 0; i < position; i++)
  {
    current = current->next_;
  }
  
  return current->data_;
}


s16 List_insertFirst(List *list, void *data, u16 bytes){
  if (list == NULL)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == NULL)
    return kErrorCode_DataNULL;

  if (list->ops_->isFull(list))
    return kErrorCode_ListFull;
  
  MemoryNode *new_node = MEMNODE_create();
  if (new_node == NULL)
    return kErrorCode_NoMemory;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Moving data to node[0x%p] with location[0x%p] and size[%d]\n", new_node, data, bytes);
#endif
  new_node->ops_->setData(new_node, data, bytes);

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Inserting node[0x%p] in the head of the list[0x%p]\n", new_node, list);
#endif
  
  new_node->next_ = list->head_;
  list->head_ = new_node;

  if (list->tail_ == NULL)
    list->tail_ = new_node;
  
  list->lenght_++;
  
  return kErrorCode_Ok;
} 


s16 List_insertLast(List *list, void *data, u16 bytes){
  if (list == NULL)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == NULL)
    return kErrorCode_DataNULL;

  if (list->ops_->isFull(list))
    return kErrorCode_ListFull;
  
  MemoryNode *new_node = MEMNODE_create();
  if (new_node == NULL)
    return kErrorCode_NoMemory;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Moving data to node[0x%p] with location[0x%p] and size[%d]\n", new_node, data, bytes);
#endif
  new_node->ops_->setData(new_node, data, bytes);

  
  //new_node->next_ = NULL;
  if (list->tail_ == NULL)
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Inserting node[0x%p] in the head of the list[0x%p] because the list is empty\n", new_node, list);
#endif
    new_node->next_ = list->head_;
    list->head_ = new_node;
  }
  else
  {
#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Inserting node[0x%p] in the tail of the list[0x%p]\n", new_node, list);
#endif
    list->tail_->next_ = new_node;
    list->tail_ = new_node;
  }
    

  list->lenght_++;
  
  return kErrorCode_Ok;
}


s16 List_insertAt(List *list, void *data, u16 bytes, u16 position){
  if (list == NULL)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == NULL)
    return kErrorCode_DataNULL;

  if (list->ops_->isFull(list))
    return kErrorCode_ListFull;
  
  MemoryNode *new_node = MEMNODE_create();
  if (new_node == NULL)
    return kErrorCode_NoMemory;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Moving data to node[0x%p] with location[0x%p] and size[%d]\n", new_node, data, bytes);
#endif
  new_node->ops_->setData(new_node, data, bytes);

  if (position > list->lenght_)
    position = list->lenght_;

  MemoryNode *current = list->head_;
  for (s16 i = 0; i < position - 1; i++)
  {
    current = current->next_;
  }

  if (current != NULL)
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Inserting node[0x%p] in the position[%d] of the list[0x%p]\n", new_node, position, list);
#endif
    new_node->next_ = current->next_;
    current->next_ = new_node;
  }
  else
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Inserting node[0x%p] in the head of the list[0x%p] because the list is empty\n", new_node, list);
#endif
    new_node->next_ = list->head_;
    list->head_ = new_node;
    list->tail_ = new_node;
  }
  
  return kErrorCode_Ok;
}

void* List_extractFirst(List *list){
  if (list == NULL)
    return kErrorCode_NULL;

  MemoryNode *extract_node = list->head_;
  if (extract_node != NULL)
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Extracting node[0x%p] from the head of the list[0x%p]\n", extract_node, list);
#endif
    list->head_ = extract_node->next_;
    if (list->lenght_ == 1)
      list->tail_ = NULL;
    return extract_node->data_;
  }
  
  return NULL;
}

MemoryNode* List_extractLastInternal(List *list)
{
  if (list == NULL)
    return NULL;
  
  MemoryNode *current = list->head_;
  if (current == NULL)
    return NULL;

  if (list->lenght_ == 1)
  {
    // only one node in the list
    list->head_ = NULL;
    list->tail_ = NULL;
  }
  else
  {
    // more than one node in the list
    while (current->next_ != list->tail_)
    {
      current = current->next_;
    }
    list->tail_ = current;
    current = current->next_;
  }

  list->lenght_--;
  return current;
}

void* List_extractLast(List *list){
  MemoryNode *extract_node = List_extractLastInternal(list);
  if (extract_node != NULL)
    return extract_node->data_;

  return NULL;
}

void* List_extractAt(List *list, u16 position){
  
  return 0;
}

s16 List_concat(List *list, List *ist_src){
  

  return 0;
}

s16 List_traverse(List *list, void (*callback)(MemoryNode *)){
 
  return kErrorCode_Ok;
}

void List_print(List *list){
  
}