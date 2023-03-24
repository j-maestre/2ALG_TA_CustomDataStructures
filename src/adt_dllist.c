#include <stdio.h>

#include "adt_list.h"
#include "common_def.h"
#include "EDK_MemoryManager/edk_memory_manager.h"


static s16 DLLIST_destroy(List *list);
static s16 DLLIST_softReset(List *list);
static s16 DLLIST_reset(List *list);
static s16 DLLIST_resize(List *list, u16 new_size);
static u16 DLLIST_capacity(List *list);
static u16 DLLIST_lenght(List *list);
static boolean DLLIST_isEmpty(List *list);
static boolean DLLIST_isFull(List *list);
static void* DLLIST_first(List *list);
static void* DLLIST_last(List *list);
static void* DLLIST_at(List *list, u16 position);
static s16 DLLIST_insertFirst(List *list, void *data, u16 bytes);
static s16 DLLIST_insertLast(List *list, void *data, u16 bytes);
static s16 DLLIST_insertAt(List *list, void *data, u16 bytes, u16 position);
static void* DLLIST_extractFirst(List *list);
static void* DLLIST_extractLast(List *list);
static void* DLLIST_extractAt(List *list, u16 position);
static s16 DLLIST_concat(List *list, List *list_src);
static s16 DLLIST_traverse(List *list, void (*callback)(MemoryNode *));
static void DLLIST_print(List *list);
static void DLLIST_initWithoutCheck(List *list);
static MemoryNode *DLLIST_extractLastInternal(List *list);
static MemoryNode* DLLIST_atInternal(List *list, u16 position);

struct list_ops_s list_ops = { .destroy = DLLIST_destroy,
                                   .softReset = DLLIST_softReset,
                                   .reset = DLLIST_reset,
                                   .resize = DLLIST_resize,
                                   .capacity = DLLIST_capacity,
                                   .length = DLLIST_lenght,
                                   .isEmpty = DLLIST_isEmpty,
                                   .isFull = DLLIST_isFull,
                                   .first = DLLIST_first,
                                   .last = DLLIST_last,
                                   .at = DLLIST_at,
                                   .insertFirst = DLLIST_insertFirst,
                                   .insertLast = DLLIST_insertLast,
                                   .insertAt = DLLIST_insertAt,
                                   .extractFirst = DLLIST_extractFirst,
                                   .extractLast = DLLIST_extractLast,
                                   .extractAt = DLLIST_extractAt,
                                   .concat = DLLIST_concat,
                                   .traverse = DLLIST_traverse,
                                   .print = DLLIST_print                   
                                   };

List* DLLIST_create(u16 capacity) { // Checked by xema and hector
  if (capacity == 0)
    return NULL;

  List *list = (List *)MM->malloc(sizeof(List));
  if (list == NULL)
    return NULL;

  DLLIST_initWithoutCheck(list);

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("List has been created with location[0x%p] and capacity[%d]\n", list, capacity);
#endif

  list->capacity_ = capacity;
  
	return list;
}

void DLLIST_initWithoutCheck(List *list){
  list->capacity_ = 0;
  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  list->ops_ = &list_ops;
}

s16 DLLIST_destroy(List *list){ // Checked by xema
  if (list == NULL)
    return kErrorCode_ListNULL;

  if (list->ops_->isEmpty(list))
  {
    MM->free(list);
    return kErrorCode_Ok;
  }

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Destroying list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif

  MemoryNode *current = list->head_;
  MemoryNode *next = current->next_;
  for (int i = 0; i < list->lenght_-1 && current != NULL; i++){
    current->ops_->free(current);
    current = next;
    next = next->next_; 
  }

  current->ops_->free(current);
  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  
  MM->free(list);

  return kErrorCode_Ok;
}

s16 DLLIST_softReset(List *list){ // Checked by xema
  if (list == NULL)
    return kErrorCode_NULL;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Soft resetting list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif
  
  MemoryNode *current = list->head_;

  while (current != NULL)
  {
    current->ops_->softFree(current);
    current = current->next_;
  }

  list->lenght_ = 0;
  
  return kErrorCode_Ok;
}

s16 DLLIST_reset(List *list){ // Checked by xema
  if (list == NULL)
    return kErrorCode_NULL;

  if (list->ops_->isEmpty(list))
    return kErrorCode_Ok;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Resetting list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif
  
  MemoryNode *current = list->head_;
  MemoryNode *next = list->head_->next_;

  while (current != NULL)
  {
    current->ops_->free(current);
    current = next;
    if (next != NULL)
      next = next->next_;
  }

  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  return kErrorCode_Ok;
}

s16 DLLIST_resize(List *list, u16 new_size){ // Checked
  if (list == NULL)
   return kErrorCode_NULL;

  MemoryNode *current = NULL;
  while (list->lenght_ > new_size)
  {
    current = DLLIST_extractLastInternal(list);
    current->ops_->free(current);
  }

  list->capacity_ = new_size;
  
  return kErrorCode_Ok;
}

u16 DLLIST_capacity(List *list){  // Checked by xema
  if (list == NULL)
    return 0;
  return list->capacity_;
}

u16 DLLIST_lenght(List *list){ // Checked by xema
  if (list == NULL)
    return 0;
  return list->lenght_;

}

boolean DLLIST_isEmpty(List *list){  // Checked by xema
  if (list == NULL)
    return False;
  return (list->lenght_ == 0);
}

boolean DLLIST_isFull(List *list){ // Checked by xema
  if (list == NULL)
    return True;
  return (list->lenght_ == list->capacity_);
}

void* DLLIST_first(List *list){  // Checked by xema
  if (list == NULL)
    return NULL;
  
  return list->head_;
}

void* DLLIST_last(List *list){  // Checked by xema
  if (list == NULL)
    return NULL;
  
  return list->tail_;
} 

void* DLLIST_at(List *list, u16 position){
  MemoryNode *node = List_atInternal(list, position);
  if (node != NULL)
    return node->data_;

  return NULL;
}

MemoryNode* DLLIST_atInternal(List *list, u16 position) // Checked by xema
{
  if (list == NULL)
    return NULL;

  MemoryNode *current = list->head_;

  if (position > list->lenght_)
    return list->tail_;
  
  for (u16 i = 0; i < position; i++)
  {
    current = current->next_;
  }
  
  return current;
}

s16 DLLIST_insertFirst(List *list, void *data, u16 bytes){ // Checked by xema
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

  if (list->tail_ == NULL){
    list->tail_ = new_node;
  }
  
  list->lenght_++;
  
  return kErrorCode_Ok;
} 


s16 List_insertLast(List *list, void *data, u16 bytes){ // Checked by xema
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

  
  // Si la lista esta vacia
  if (list->tail_ == NULL)
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Inserting node[0x%p] in the head of the list[0x%p] because the list is empty\n", new_node, list);
#endif
    new_node->next_ = NULL;
    list->head_ = new_node;
    list->tail_ = new_node;
    
  // Si tiene cosas dentro
  }else{
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


s16 DLLIST_insertAt(List *list, void *data, u16 bytes, u16 position){ // Checked by xema
  if (list == NULL)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == NULL)
    return kErrorCode_DataNULL;

  if (list->ops_->isFull(list))
    return kErrorCode_ListFull;

  if (list->ops_->isEmpty(list) || position == 0) {
    return list->ops_->insertFirst(list,data,bytes);
  }
  
  if (position > list->lenght_) {
    return list->ops_->insertLast(list, data, bytes);
  }

  MemoryNode *new_node = MEMNODE_create();
  if (new_node == NULL)
    return kErrorCode_NoMemory;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Moving data to node[0x%p] with location[0x%p] and size[%d]\n", new_node, data, bytes);
#endif
  new_node->ops_->setData(new_node, data, bytes); 

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
    new_node->next_ = NULL;
    list->head_ = new_node;
    list->tail_ = new_node;
  }

  list->lenght_++;
  
  return kErrorCode_Ok;
}

void* DLLIST_extractFirst(List *list){ // Checked by xema
  if (list == NULL)
    return kErrorCode_NULL;

  MemoryNode *extract_node = list->head_;
  void* extract_data;
  if (extract_node != NULL)
  {
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Extracting node[0x%p] from the head of the list[0x%p]\n", extract_node, list);
#endif
    list->head_ = extract_node->next_;
    if (list->lenght_ == 1){
      list->tail_ = NULL;
      list->head_ = NULL;
    }
    
    list->lenght_--;
    extract_data = extract_node->data_;
    extract_node->ops_->softFree(extract_node);
    return extract_data;
  }
  
  return NULL;
}

MemoryNode* DLLIST_extractLastInternal(List *list){ // Checked by xema
  if (list == NULL)
    return NULL;
  
  MemoryNode *current = list->head_;
  if (current == NULL)
    return NULL;

  if (list->lenght_ == 1){
    // only one node in the list
    list->head_ = NULL;
    list->tail_ = NULL;
  }else{
    // more than one node in the list
    // Llegamos hasta el penultimo
    while (current->next_->next_ != NULL)
    {
      current = current->next_;
    }
    list->tail_ = current;
    current = current->next_;
    list->tail_->next_ = NULL;
  }
#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Extracting node[0x%p] from the head of the list[0x%p]\n", current, list);
#endif
  list->lenght_--;
  return current;
}

void* DLLIST_extractLast(List *list){ // Checked by xema
  MemoryNode *extract_node = DLLIST_extractLastInternal(list);
  void* data;
  if (extract_node != NULL) 
  {
    data = extract_node->data_;
    extract_node->ops_->softFree(extract_node);
  }
  else
  {
    data = NULL;
  }



  return data;
}


void* DLLIST_extractAt(List *list, u16 position){ // Checked by xema
  if (list == NULL)
    return NULL;

  if (list->lenght_ < position)
    position = list->lenght_;
  
  MemoryNode *current = list->head_;
  for (s16 i = 0; i < position - 1; i++)
  {
    current = current->next_;
  }

  MemoryNode *extract_node = current->next_;
  if (extract_node != NULL)
    current->next_ = extract_node->next_;
  else
    current->next_ = NULL;
  
  
  if (extract_node != NULL)
  {
    list->lenght_--;
    void *data = extract_node->data_;
    extract_node->ops_->softFree(extract_node);
    return data;
  }
  
  return NULL;
}

s16 DLLIST_concat(List *list, List *list_src){ // Checked by xema
  if (list == NULL || list_src == NULL)
    return kErrorCode_NULL;

  u16 new_capacity = list->capacity_ + list_src->capacity_;

  list->ops_->resize(list, new_capacity);

  MemoryNode *copy_node = MEMNODE_create();
  MemoryNode *current;
  for (u16 i = 0; i < list_src->lenght_; i++)
  {
    current = DLLIST_atInternal(list_src, i);
    copy_node->ops_->memCopy(copy_node, current->data_, current->size_);
    list->ops_->insertLast(list, copy_node->data_, copy_node->size_);
    copy_node->ops_->softReset(copy_node);
  }
  
  copy_node->ops_->softFree(copy_node);
  
  return kErrorCode_Ok;
}

s16 DLLIST_traverse(List *list, void (*callback)(MemoryNode *)){ // Checked by xema
  if (list == NULL)
    return kErrorCode_NULL;

  if (callback == NULL)
    return kErrorCode_CallBackNULL;
  
  MemoryNode *current  = list->head_;
  for (u16 i = 0; i < list->lenght_; i++)
  {
    callback(current);
    current = current->next_;
  }
  
  return kErrorCode_Ok;
}

void DLLIST_print(List *list){
  if (list == NULL)
    return;
  
  MemoryNode *current  = list->head_;
  for (u16 i = 0; i < list->lenght_ && current != NULL; i++)
  {
    current->ops_->print(current);
    current = current->next_;
  }
}