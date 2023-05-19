#include "dllist.h"

#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

DLList::DLList(u16 size) : head_(nullptr), tail_(nullptr), capacity_(size), lenght_(0)
{
  
}

DLList::DLList(DLList&& other)
{
  head_ = other.head_;
  other.head_ = nullptr;
  tail_ = other.tail_;
  other.tail_ = nullptr;
  capacity_ = other.capacity_;
  lenght_ = other.lenght_;
}

DLList& DLList::operator=(DLList&& other)
{
  if (this != &other)
  {
    head_ = other.head_;
    other.head_ = nullptr;
    tail_ = other.tail_;
    other.tail_ = nullptr;
    capacity_ = other.capacity_;
    lenght_ = other.lenght_;
  }

  return *this;
}

DLList::~DLList()
{
  
}

void* DLList::operator new(size_t count)
{
  return MM->malloc(count);
}

void DLList::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* DLList::operator new [](size_t count)
{
  return MM->malloc(count);
}

void DLList::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}

DLList* DLList::Create(u16 size)
{
  if (size <= 0) return nullptr;
  return new DLList(size);
}

s16 DLList::destroy()
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (this->lenght_ == 0)
  {
    delete this;
    return kErrorCode_Ok;
  }

  MemoryNode *current = this->tail_;
  MemoryNode *next = current->previous_;

  MemoryNode *destroyed = NULL;
  while (this->lenght_ > 0)
  {
    destroyed = extractLast();
    if (destroyed != NULL)
    {
      destroyed->free();
    }
  }

  delete this;
  return kErrorCode_Ok;
}

s16 DLList::softReset()
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (this->lenght_ == 0)
  {
    return kErrorCode_Ok;
  }

  MemoryNode *destroy = NULL;
  while (this->lenght_ > 0)
  {
    destroy = extractLast();
    if (destroy != NULL)
    {
      destroy->softFree();
    }
  }

  return kErrorCode_Ok;
}

s16 DLList::reset()
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  if (this->lenght_ == 0)
  {
    return kErrorCode_Ok;
  }

  MemoryNode *destroy = NULL;
  while (this->lenght_ > 0)
  {
    destroy = extractLast();
    if (destroy != NULL)
    {
      destroy->free();
    }
  }

  return kErrorCode_Ok;
}

s16 DLList::resize(u16 new_size)
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  MemoryNode *destroy = NULL;
  while (this->lenght_ > new_size)
  {
    destroy = extractLast();

    if (destroy != NULL)
    {
      destroy->free();
    }
  }
  this->capacity_ = new_size;

  return kErrorCode_Ok;
}

u16 DLList::capacity()
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return this->capacity_;
}

u16 DLList::length()
{
  if (this == NULL)
  {
    return kErrorCode_ListNULL;
  }

  return this->lenght_;
}

boolean DLList::isEmpty()
{
  if (this == NULL)
  {
    return False;
  }

  return this->lenght_ == 0;
}

boolean DLList::isFull()
{
  if (this == NULL)
  {
    return True;
  }

  return this->lenght_ == this->capacity_;
}

MemoryNode* DLList::first()
{
  if (this == NULL)
  {
    return nullptr;
  }

  return this->head_;
}

MemoryNode* DLList::last()
{
  if (this == NULL)
  {
    return nullptr;
  }
  return this->tail_;
}

MemoryNode* DLList::at(u16 position)
{
  if (this == NULL)
  {
    return nullptr;
  }
  if (position > this->lenght_)
  {
    if (this->tail_ != NULL)
    {
      return this->tail_;
    }
    return NULL;
  }
  MemoryNode *current = this->head_;
  for (u32 i = 0; i < position; i++)
  {
    current = current->next_;
  }
  return current;
}

s16 DLList::insertFirst(void* data, u16 bytes)
{
  if (this == NULL)
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

  if (this->lenght_ == this->capacity_)
  {
    return kErrorCode_ListFull;
  }

  MemoryNode *new_node = new MemoryNode();
  new_node->setData(data, bytes);

  new_node->next_ = this->head_;
  new_node->previous_ = NULL;

  if (this->head_ != NULL)
  {
    this->head_->previous_ = new_node;
  }
  if (this->tail_ == NULL)
  {
    this->tail_ = new_node;
  }

  this->head_ = new_node;
  this->lenght_++;

  return kErrorCode_Ok;
}

s16 DLList::insertLast(void* data, u16 bytes)
{
  if (this == NULL)
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

  if (this->lenght_ == this->capacity_)
  {
    return kErrorCode_ListFull;
  }

  MemoryNode* new_node = new MemoryNode();
  new_node->setData(data, bytes);

  new_node->next_ = NULL;
  new_node->previous_ = this->tail_;

  if (this->tail_ != NULL)
  {
    this->tail_->next_ = new_node;
  }
  if (this->head_ == NULL)
  {
    this->head_ = new_node;
  }

  this->tail_ = new_node;
  this->lenght_++;

  return kErrorCode_Ok;
}

s16 DLList::insertAt(void* data, u16 bytes, u16 position)
{
  if (this == NULL)
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

  if (this->lenght_ == this->capacity_)
  {
    return kErrorCode_ListFull;
  }

  
  if (position >= this->lenght_)
  {
    return insertLast(data, bytes);
  }
  else
  {
    if (position == 0)
    {
      return insertFirst(data, bytes);
    }
    else{

      MemoryNode* new_node = new MemoryNode();
      new_node->setData(data, bytes);

      MemoryNode* node = this->head_;
      for (u32 i = 0; i < position - 1; i++)
      {
        node = node->next_;
      }
      new_node->next_ = node->next_;
      node->next_->previous_ = new_node;
      new_node->previous_ = node;
      node->next_ = new_node;

      this->lenght_++;

      return kErrorCode_Ok;
    }
  }
}

MemoryNode* DLList::extractFirst()
{
  if (this == NULL)
  {
    return NULL;
  }

  MemoryNode* extract_node = this->head_;

  if (this->lenght_ == 0)
  {
    return NULL;
  }

  //extract_node->previous_ = NULL;
  this->head_ = extract_node->next_;
  if (this->head_ != NULL)
  {
    this->head_->previous_ = NULL;
  }
  else
  {
    this->tail_ = NULL;
  }

  this->lenght_--;

  return extract_node;
}

MemoryNode* DLList::extractAt(u16 position)
{
  if (this == NULL)
  {
    return NULL;
  }

  MemoryNode* node = NULL;
  if (position > this->lenght_)
  {
    node = extractLast();
  }
  else
  {
    if (position == 0)
    {
      node = extractFirst();
    }
    else
    {
      MemoryNode* extract_node = this->head_;

      if (this->lenght_ == 0)
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

      this->lenght_--;

      node = extract_node;
    }
  }
  return node;
}

MemoryNode* DLList::extractLast()
{
  if (this == NULL)
  {
    return NULL;
  }

  MemoryNode* extract_node = this->tail_;

  if (this->lenght_ == 0)
  {
    return NULL;
  }
  
  this->tail_ = extract_node->previous_;
  if (this->tail_ != NULL)
  {
    this->tail_->next_ = NULL;
  }
  else
  {
    this->head_ = NULL;
  }

  this->lenght_--;

  return extract_node;
}

s16 DLList::concat(DLList* list_src)
{
  if (this == NULL || list_src == NULL)
  {
    return kErrorCode_ListNULL;
  }

  u16 new_capacity = this->capacity_ + list_src->capacity_;

  resize(new_capacity);

  MemoryNode* copy_node = new MemoryNode();
  MemoryNode* current;
  for (u16 i = 0; i < list_src->lenght_; i++)
  {
    current = list_src->at(i);
    copy_node->memCopy(current->data_, current->size_);

    insertLast(copy_node->data_, copy_node->size_);
    copy_node->softReset();
  }

  copy_node->softFree();

  return kErrorCode_Ok;
}

s16 DLList::traverse(void (* callback)(MemoryNode*))
{
  if (this == NULL)
    return kErrorCode_NULL;

  if (callback == NULL)
    return kErrorCode_CallBackNULL;

  MemoryNode* current = this->head_;
  for (u16 i = 0; i < this->lenght_; i++)
  {
    callback(current);
    current = current->next_;
  }

  return kErrorCode_Ok;
}

void DLList::print()
{
  if (this == NULL)
    return;

  MemoryNode* current = this->head_;
  for (u16 i = 0; i < this->lenght_ && current != NULL; i++)
  {
    current->print();
    current = current->next_;
  }
}


