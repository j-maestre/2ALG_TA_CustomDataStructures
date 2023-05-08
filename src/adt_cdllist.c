#include <stdio.h>

#include "adt_cdllist.h"
#include "common_def.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

static void CDLLIST_initWithoutCheck(List* list);
static s16 CDLLIST_destroyWithoutCheck(List *list);
static s16 CDLLIST_destroy(List* list);
static s16 CDLLIST_softResetWithoutCheck(List *list);
static s16 CDLLIST_softReset(List* list);
static s16 CDLLIST_resetWithoutCheck(List* list);
static s16 CDLLIST_reset(List *list);
static s16 CDLLIST_resizeWithoutCheck(List* list, u16 new_size);
static s16 CDLLIST_resize(List *list, u16 new_size);
static u16 CDLLIST_capacity(List *list);
static u16 CDLLIST_lenght(List *list);
static boolean CDLLIST_isEmpty(List *list);
static boolean CDLLIST_isFull(List *list);
static MemoryNode* CDLLIST_firstWithoutCheck(List* list);
static void* CDLLIST_first(List *list);
static MemoryNode* CDLLIST_lastWithoutCheck(List* list);
static void* CDLLIST_last(List *list);
static MemoryNode* CDLLIST_atWithoutCheck(List* list, u16 position);
static void* CDLLIST_at(List *list, u16 position);
static s16 CDLLIST_insertFirstWithoutCheck(List* list, void* data, u16 bytes);
static s16 CDLLIST_insertFirst(List *list, void *data, u16 bytes);
static s16 CDLLIST_insertLastWithoutCheck(List* list, void* data, u16 bytes);
static s16 CDLLIST_insertLast(List *list, void *data, u16 bytes);
static s16 CDLLIST_insertAtWithoutCheck(List* list, void* data, u16 bytes, u16 position);
static s16 CDLLIST_insertAt(List *list, void *data, u16 bytes, u16 position);
static MemoryNode* CDLLIST_extractFirstWithoutCheck(List* list);
static void* CDLLIST_extractFirst(List *list);
static MemoryNode* CDLLIST_extractLastWithoutCheck(List* list);
static void* CDLLIST_extractLast(List *list);
static MemoryNode* CDLLIST_extractAtWithoutCheck(List* list, u16 position);
static void* CDLLIST_extractAt(List *list, u16 position);
static s16 CDLLIST_concatWithoutCheck(List* list, List* list_src);
static s16 CDLLIST_concat(List *list, List *list_src);
static s16 CDLLIST_traverse(List *list, void (*callback)(MemoryNode *));
static void CDLLIST_print(List *list);

struct list_ops_s list_ops_cd = { .destroy = CDLLIST_destroy,
                                   .softReset = CDLLIST_softReset,
                                   .reset = CDLLIST_reset,
                                   .resize = CDLLIST_resize,
                                   .capacity = CDLLIST_capacity,
                                   .length = CDLLIST_lenght,
                                   .isEmpty = CDLLIST_isEmpty,
                                   .isFull = CDLLIST_isFull,
                                   .first = CDLLIST_first,
                                   .last = CDLLIST_last,
                                   .at = CDLLIST_at,
                                   .insertFirst = CDLLIST_insertFirst,
                                   .insertLast = CDLLIST_insertLast,
                                   .insertAt = CDLLIST_insertAt,
                                   .extractFirst = CDLLIST_extractFirst,
                                   .extractLast = CDLLIST_extractLast,
                                   .extractAt = CDLLIST_extractAt,
                                   .concat = CDLLIST_concat,
                                   .traverse = CDLLIST_traverse,
                                   .print = CDLLIST_print                   
                                   };

List* CDLLIST_create(u16 capacity) {
  if (capacity == 0)
    return NULL;

  List *list = (List *)MM->malloc(sizeof(List));
  if (list == NULL)
    return NULL;

  CDLLIST_initWithoutCheck(list);

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("List has been created with location[0x%p] and capacity[%d]\n", list, capacity);
#endif

  list->capacity_ = capacity;
  
	return list; 
}

void CDLLIST_initWithoutCheck(List *list){
  list->capacity_ = 0;
  list->lenght_ = 0;
  list->head_ = NULL;
  list->tail_ = NULL;
  list->ops_ = &list_ops_cd;
}

s16 CDLLIST_destroyWithoutCheck(List* list)
{
  if (list->lenght_ == 0)
  {
    MM->free(list);
    return kErrorCode_Ok;
  }

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Destroying list in location[0x%p] with capacity[%d] and length[%d]\n", list, list->capacity_, list->lenght_);
#endif

  MemoryNode *current = list->tail_;
  MemoryNode *next = current->previous_;

  MemoryNode *destroyed = NULL;
  while (list->lenght_ > 0)
  {
    destroyed = CDLLIST_extractLastWithoutCheck(list);
    if (destroyed != NULL)
    {
      destroyed->ops_->free(destroyed);
    }
  }

  MM->free(list);
  return kErrorCode_Ok;
}
s16 CDLLIST_destroy(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return CDLLIST_destroyWithoutCheck(list);
}

s16 CDLLIST_softResetWithoutCheck(List* list)
{
  if (list->lenght_)
  {
    return kErrorCode_Ok;
  }

  MemoryNode *destroy = NULL;
  while (list->lenght_ > 0)
  {
    destroy = CDLLIST_extractLastWithoutCheck(list);
    if (destroy != NULL)
    {
      destroy->ops_->softFree(destroy);
    }
  }

  return kErrorCode_Ok;
}

s16 CDLLIST_softReset(List* list) 
{
  if (list != NULL)
  {
    return kErrorCode_ListNULL;
  }

  return CDLLIST_softResetWithoutCheck(list);
}

s16 CDLLIST_resetWithoutCheck(List* list)
{
  if (list->lenght_ == 0)
  {
    return kErrorCode_Ok;
  }

  MemoryNode *destroy = NULL;
  while (list->lenght_ > 0)
  {
    destroy = CDLLIST_extractLastWithoutCheck(list);
    if (destroy != NULL)
    {
      destroy->ops_->free(destroy);
    }
  }

  return kErrorCode_Ok;
}

s16 CDLLIST_reset(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return CDLLIST_resetWithoutCheck(list);
}

s16 CDLLIST_resizeWithoutCheck(List* list, u16 new_size)
{

  MemoryNode *destroy = NULL;
  while (list->lenght_ > new_size)
  {
    destroy = CDLLIST_extractLastWithoutCheck(list);

    if (destroy != NULL)
    {
      destroy->ops_->free(destroy);
    }
  }
  list->capacity_ = new_size;

  return kErrorCode_Ok;
}

s16 CDLLIST_resize(List* list, u16 new_size)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return CDLLIST_resizeWithoutCheck(list, new_size);
}

u16 CDLLIST_capacity(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return list->capacity_;
}

u16 CDLLIST_lenght(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return list->lenght_;
}

boolean CDLLIST_isEmpty(List* list)
{
  if (list == NULL)
  {
    return False;
  }

  return list->lenght_ == 0;
}

boolean CDLLIST_isFull(List* list)
{
  if (list == NULL)
  {
    return True;
  }

  return list->lenght_ == list->capacity_;
}

MemoryNode* CDLLIST_firstWithoutCheck(List* list)
{
  return list->head_;
}

void* CDLLIST_first(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }
  MemoryNode *node = CDLLIST_firstWithoutCheck(list);
  if (node != NULL)
  {
    return node->data_;
  } 
  return NULL;
}

MemoryNode* CDLLIST_lastWithoutCheck(List* list)
{
  return list->tail_;
}

void* CDLLIST_last(List* list)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }
  MemoryNode* node = CDLLIST_lastWithoutCheck(list);
  if (node != NULL)
  {
    return node->data_;
  }
  return NULL;
}

MemoryNode* CDLLIST_atWithoutCheck(List* list, u16 position)
{
  MemoryNode *current = list->head_;
  for (u32 i = 0; i < position; i++)
  {
    current = current->next_;
  }
  return current;
}

void* CDLLIST_at(List* list, u16 position)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }
  if (position > list->lenght_)
  {
    if (list->tail_ != NULL)
    {
      return list->tail_->data_;
    }
    return NULL;
  }

  MemoryNode *node = CDLLIST_atWithoutCheck(list, position);
  if (node != NULL)
  {
    return node->data_;
  }
  return NULL;
}

s16 CDLLIST_insertFirstWithoutCheck(List* list, void* data, u16 bytes) // TODO revise
{
  MemoryNode *new_node = MEMNODE_create();
  new_node->ops_->setData(new_node, data, bytes);

  new_node->next_ = list->head_;
  new_node->previous_ = NULL;
  
#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data inserted at the head of the list[0x%p] a new node with location[0x%p] and data[0x%p] with size[%d]\n", list, new_node, new_node->data_, new_node->size_);
#endif // VERBOSE_

  if (list->head_ != NULL)
  {
    list->head_->previous_ = new_node;
  }
  if (list->tail_ == NULL)
  {
    list->tail_ = new_node;
    new_node->next_ = list->head_;
  }

  list->head_ = new_node;
  list->head_->previous_ = list->tail_;
  list->lenght_++;

  return kErrorCode_Ok;
}

s16 CDLLIST_insertFirst(List* list, void* data, u16 bytes)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (data == NULL)
  {
    return kErrorCode_DataNULL;
  }

  if (bytes == 0)
  {
    return kErrorCode_ZeroBytes;
  }

  if (list->lenght_ == list->capacity_)
  {
    return kErrorCode_ListFull;
  }

  return CDLLIST_insertFirstWithoutCheck(list, data, bytes);
}

s16 CDLLIST_insertLastWithoutCheck(List* list, void* data, u16 bytes) // TODO revise
{
  MemoryNode* new_node = MEMNODE_create();
  new_node->ops_->setData(new_node, data, bytes);

  new_node->next_ = NULL;
  new_node->previous_ = list->tail_;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data inserted at the tail of the list[0x%p] a new node with location[0x%p] and data[0x%p] with size[%d]\n", list, new_node, new_node->data_, new_node->size_);
#endif // VERBOSE_

  if (list->tail_ != NULL)
  {
    list->tail_->next_ = new_node;
  }
  if (list->head_ == NULL)
  {
    list->head_ = new_node;
  }

  list->tail_ = new_node;
  list->tail_->next_ = list->head_;
  list->head_->previous_ = list->tail_;
  list->lenght_++;

  return kErrorCode_Ok;
}

s16 CDLLIST_insertLast(List* list, void* data, u16 bytes)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (data == NULL)
  {
    return kErrorCode_DataNULL;
  }

  if (bytes == 0)
  {
    return kErrorCode_ZeroBytes;
  }

  if (list->lenght_ == list->capacity_)
  {
    return kErrorCode_ListFull;
  }

  return CDLLIST_insertLastWithoutCheck(list, data, bytes);
}

s16 CDLLIST_insertAtWithoutCheck(List* list, void* data, u16 bytes, u16 position)
{
  MemoryNode* new_node = MEMNODE_create();
  new_node->ops_->setData(new_node, data, bytes);

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data inserted at position[%d] of the list[0x%p] a new node with location[0x%p] and data[0x%p] with size[%d]\n", position, list, new_node, new_node->data_, new_node->size_);
#endif // VERBOSE_

  MemoryNode* node = list->head_;
  for (u32 i = 0; i < position - 1; i++)
  {
    node = node->next_;
  }
  new_node->next_ = node->next_;
  node->next_->previous_ = new_node;
  new_node->previous_ = node;
  node->next_ = new_node;

  list->lenght_++;

  return kErrorCode_Ok;
}

s16 CDLLIST_insertAt(List* list, void* data, u16 bytes, u16 position)
{
  if (list == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (data == NULL)
  {
    return kErrorCode_DataNULL;
  }

  if (bytes == 0)
  {
    return kErrorCode_ZeroBytes;
  }

  if (list->lenght_ == list->capacity_)
  {
    return kErrorCode_ListFull;
  }

  MemoryNode* node = NULL;
  if (position >= list->lenght_)
  {
    return CDLLIST_insertLastWithoutCheck(list, data, bytes);
  }
  else
  {
    if (position == 0)
    {
      return CDLLIST_insertFirstWithoutCheck(list, data, bytes);
    }
    else{

      return CDLLIST_insertAtWithoutCheck(list, data, bytes, position);
    }
  }
  return kErrorCode_Ok;
}

MemoryNode* CDLLIST_extractFirstWithoutCheck(List* list) // TODO revise
{
  MemoryNode* extract_node = list->head_;

  if (list->lenght_ == 0)
  {
    return NULL;
  }

  //extract_node->previous_ = NULL;
  list->head_ = extract_node->next_;
  if (list->head_ != NULL)
  {
    list->head_->previous_ = list->tail_;
    list->tail_->next_ = list->head_;
  }
  else
  {
    list->tail_ = NULL;
    list->head_->next_ = NULL;
    list->head_->previous_ = NULL;
    list->tail_->next_ = NULL;
    list->tail_->previous_ = NULL;
  }

  list->lenght_--;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data extracted at the head of the list[0x%p], node extracted with location[0x%p] and data[0x%p] with size[%d]\n", list, extract_node, extract_node->data_, extract_node->size_);
#endif // VERBOSE_

  return extract_node;
}

void* CDLLIST_extractFirst(List* list) 
{
  if (list == NULL)
  {
    return NULL;
  }

  MemoryNode* node = CDLLIST_extractFirstWithoutCheck(list);
  void* data = NULL;
  if (node != NULL)
  {
    data = node->data_;
    node->ops_->softFree(node);
  }
  return data;
}

MemoryNode* CDLLIST_extractLastWithoutCheck(List* list) // TODO revise
{
  MemoryNode* extract_node = list->tail_;

  if (list->lenght_ == 0)
  {
    return NULL;
  }

  //extract_node->next_ = NULL;
  list->tail_ = extract_node->previous_;
  if (list->tail_ != NULL)
  {
    list->tail_->next_ = NULL;
    list->head_->previous_ = list->tail_;
    list->tail_->next_ = list->head_;

  // Si entra aqui, acabamos de dejar la lista vacia
  }else{
    list->head_ = NULL;
    list->head_->next_ = NULL;
    list->head_->previous_ = NULL;
    list->tail_->next_ = NULL;
    list->tail_->previous_ = NULL;

  }

  list->lenght_--;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data extracted at the tail of the list[0x%p], node extracted with location[0x%p] and data[0x%p] with size[%d]\n", list, extract_node, extract_node->data_, extract_node->size_);
#endif // VERBOSE_

  return extract_node;
}

void* CDLLIST_extractLast(List* list)
{
  if (list == NULL)
  {
    return NULL;
  }

  MemoryNode* node = CDLLIST_extractLastWithoutCheck(list);
  void* data = NULL;
  if (node != NULL)
  {
    data = node->data_;
    node->ops_->softFree(node);
  }
  return data;
}

MemoryNode* CDLLIST_extractAtWithoutCheck(List* list, u16 position)
{
  MemoryNode* extract_node = list->head_;

  if (list->lenght_ == 0)
  {
    return NULL;
  }

  for (u32 i = 0; i < position; i++)
  {
    extract_node = extract_node->next_;
  }

  extract_node->previous_->next_ = extract_node->next_;
  extract_node->next_->previous_ = extract_node->previous_;

  extract_node->next_ = NULL;
  extract_node->previous_ = NULL;

  list->lenght_--;

#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("Data extracted at position[%d] of the list[0x%p], node extracted with location[0x%p] and data[0x%p] with size[%d]\n", position, list, extract_node, extract_node->data_, extract_node->size_);
#endif // VERBOSE_

  return extract_node;
}

void* CDLLIST_extractAt(List* list, u16 position)
{
  if (list == NULL)
  {
    return NULL;
  }

  MemoryNode* node = NULL;
  void* data = NULL;
  if (position > list->lenght_)
  {
    node = CDLLIST_extractLastWithoutCheck(list);
  }
  else
  {
    if (position == 0)
    {
      node = CDLLIST_extractFirstWithoutCheck(list);
    }
    else
    {
      node = CDLLIST_extractAtWithoutCheck(list, position);
    }
  }

  if (node != NULL)
  {
    data = node->data_;
    node->ops_->softFree(node);
  }

  return data;
}

s16 CDLLIST_concatWithoutCheck(List* list, List* list_src)
{
  u16 new_capacity = list->capacity_ + list_src->capacity_;

  CDLLIST_resizeWithoutCheck(list, new_capacity);

  MemoryNode* copy_node = MEMNODE_create();
  MemoryNode* current;
  for (u16 i = 0; i < list_src->lenght_; i++)
  {
    current = CDLLIST_atWithoutCheck(list_src, i);
    copy_node->ops_->memCopy(copy_node, current->data_, current->size_);
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Data copyed in node[0x%p] with data[0x%p] and size[%d]\n", copy_node, copy_node->data_, copy_node->size_);
#endif // VERBOSE_
    CDLLIST_insertLastWithoutCheck(list, copy_node->data_, copy_node->size_);
    copy_node->ops_->softReset(copy_node);
  }

  copy_node->ops_->softFree(copy_node);

  return kErrorCode_Ok;
}

s16 CDLLIST_concat(List* list, List* list_src)
{
  if (list == NULL || list_src == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return CDLLIST_concatWithoutCheck(list, list_src);
}

s16 CDLLIST_traverse(List* list, void (*callback)(MemoryNode*))
{
  if (list == NULL)
    return kErrorCode_NULL;

  if (callback == NULL)
    return kErrorCode_CallBackNULL;

  MemoryNode* current = list->head_;
  for (u16 i = 0; i < list->lenght_; i++)
  {
    callback(current);
    current = current->next_;
  }

  return kErrorCode_Ok;
}

void CDLLIST_print(List* list)
{
  if (list == NULL)
    return;

  MemoryNode* current = list->head_;
  for (u16 i = 0; i < list->lenght_ && current != NULL; i++)
  {
    current->ops_->print(current);
    current = current->next_;
  }
}