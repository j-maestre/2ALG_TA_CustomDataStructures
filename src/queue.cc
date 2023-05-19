#include "queue.h"

#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

Queue::Queue(u16 size)
{
  storage_ = List::Create(size);
}

Queue::Queue(Queue&& other)
{
  storage_ = other.storage_;
  other.storage_ = nullptr;
}

Queue::~Queue()
{
  
}

Queue& Queue::operator=(Queue&& other)
{
  if (this != &other)
  {
    storage_ = other.storage_;
    other.storage_ = nullptr;
  }

  return *this;
}

Queue* Queue::Create(u16 size)
{
  return new Queue(size);
}

void* Queue::operator new(size_t count)
{
  return MM->malloc(count);
}

void Queue::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* Queue::operator new [](size_t count)
{
  return MM->malloc(count);
}

void Queue::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}

s16 Queue::reset()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->reset();
}

s16 Queue::enqueue(void* data, u16 bytes)
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->insertLast(data, bytes);
}

boolean Queue::isEmpty()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->isEmpty();
}

boolean Queue::isFull()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->isFull();
}

u16 Queue::capacity()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->capacity();
}

s16 Queue::resize(u16 new_size)
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->resize(new_size);
}

void* Queue::dequeue()
{
  if (this == NULL)
  {
    return NULL;
  }

  if (this->storage_ == NULL)
  {
    return NULL;
  }

  return this->storage_->extractFirst();
}

u16 Queue::length()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->length();
}

void* Queue::front()
{
  if (this == NULL)
  {
    return NULL;
  }

  if (this->storage_ == NULL)
  {
    return NULL;
  }

  return this->storage_->first();
}

void* Queue::back()
{
  if (this == NULL)
  {
    return NULL;
  }

  if (this->storage_ == NULL)
  {
    return NULL;
  }

  return this->storage_->last();
}

s16 Queue::concat(Queue* queue_src)
{
  if (this == NULL || queue_src == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  return this->storage_->concat(queue_src->storage_);
}

s16 Queue::destroy()
{
  if (this == NULL)
  {
    return kErrorCode_NULL;
  }

  if (this->storage_ == NULL)
  {
    return kErrorCode_NULL;
  }

  s16 result = this->storage_->destroy();

  if (result == kErrorCode_Ok)
  {
    delete this;
  }

  return result;
}

void Queue::print()
{
  if (this == NULL)
  {
    return;
  }

  if (this->storage_ == NULL)
  {
    return;
  }

  this->storage_->print();
}