
#include "EDK_MemoryManager/edk_memory_manager.h"

#include "common_def.h"
#include "adt_memory_node.h"
#include "adt_list.h"

#include "adt_queue.h"

static s16 QUEUE_reset(Queue *queue);
static s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes);
static boolean QUEUE_isEmpty(Queue *queue);
static boolean QUEUE_isFull(Queue *queue);
static u16 QUEUE_capacity(Queue *queue);
static s16 QUEUE_resize(Queue *queue, u16 new_size);
static void* QUEUE_dequeue(Queue *queue);
static u16 QUEUE_length(Queue *queue);
static void* QUEUE_front(Queue *queue);
static void* QUEUE_back(Queue *queue);
static s16 QUEUE_concat(Queue *queue, Queue *queue_src);
static s16 QUEUE_destroy(Queue *queue);
static void QUEUE_print(Queue *queue);

struct queue_ops_s queue_ops = {
                              .reset = QUEUE_reset,
                              .enqueue = QUEUE_enqueue,
                              .isEmpty = QUEUE_isEmpty,
                              .isFull = QUEUE_isFull,
                              .capacity = QUEUE_capacity,
                              .resize = QUEUE_resize,
                              .dequeue = QUEUE_dequeue,
                              .length = QUEUE_length,
                              .front = QUEUE_front,
                              .back = QUEUE_back,
                              .concat = QUEUE_concat,
                              .destroy = QUEUE_destroy,
                              .print = QUEUE_print,
};


Queue* QUEUE_create(u16 size)
{
  if (size == 0)
  {
    return kErrorCode_ZeroBytes;
  }
  
  Queue *queue = MM->malloc(sizeof(Queue));

  if (queue == NULL)
  {
    return NULL;
  }

  queue->storage_ = LIST_create(size);

  if (queue->storage_ == NULL)
  {
    MM->free(queue);
    return NULL;
  }

  queue->ops_ = &queue_ops;
  
  return queue;
}

s16 QUEUE_reset(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->reset(queue->storage_);
}

s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->insertLast(queue->storage_, data, bytes);
}

boolean QUEUE_isEmpty(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->isEmpty(queue->storage_);
}

boolean QUEUE_isFull(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->isFull(queue->storage_);
}

u16 QUEUE_capacity(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->capacity(queue->storage_);
}

s16 QUEUE_resize(Queue *queue, u16 new_size)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->resize(queue->storage_, new_size);
}

void* QUEUE_dequeue(Queue *queue)
{
  if (queue == NULL)
  {
    return NULL;
  }

  if (queue->storage_ == NULL)
  {
    return NULL;
  }

  return queue->storage_->ops_->extractFirst(queue->storage_);
}
u16 QUEUE_length(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->length(queue->storage_);
}

void* QUEUE_front(Queue *queue)
{
  if (queue == NULL)
  {
    return NULL;
  }

  if (queue->storage_ == NULL)
  {
    return NULL;
  }

  return queue->storage_->ops_->first(queue->storage_);
}

void* QUEUE_back(Queue *queue)
{
  if (queue == NULL)
  {
    return NULL;
  }

  if (queue->storage_ == NULL)
  {
    return NULL;
  }

  return queue->storage_->ops_->last(queue->storage_);
}

s16 QUEUE_concat(Queue *queue, Queue *queue_src)
{
  if (queue == NULL || queue_src == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return queue->storage_->ops_->concat(queue->storage_, queue_src->storage_);
}

s16 QUEUE_destroy(Queue *queue)
{
  if (queue == NULL)
  {
    return kErrorCode_NULL;
  }

  if (queue->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  s16 result = queue->storage_->ops_->destroy(queue->storage_);

  if (result == kErrorCode_Ok)
  {
    MM->free(queue);
  }

  return result;
}

void QUEUE_print(Queue *queue)
{
  if (queue == NULL)
  {
    return;
  }

  if (queue->storage_ == NULL)
  {
    return;
  }

  queue->storage_->ops_->print(queue->storage_);
}