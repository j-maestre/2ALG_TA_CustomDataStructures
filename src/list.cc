#include "list.h"
#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

List::List(u16 size) : head_(nullptr), tail_(nullptr), capacity_(size), lenght_(0)
{
  
}

List::List(List&& other)
{
  head_ = other.head_;
  tail_ = other.tail_;
  capacity_ = other.capacity_;
  lenght_ = other.lenght_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

List::~List()
{
  
}

List& List::operator=(List&& other)
{
  if (this != &other)
  {
    head_ = other.head_;
    tail_ = other.tail_;
    capacity_ = other.capacity_;
    lenght_ = other.lenght_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  return *this;
}

List* List::Create(u16 size)
{
  if (size <= 0) return nullptr;
  return new List(size);
}

s16 List::destroy()
{
  if (this == nullptr)
    return kErrorCode_ListNULL;

  if (this->isEmpty())
  {
    delete this;
    return kErrorCode_Ok;
  }

  MemoryNode *current = this->head_;
  MemoryNode *next = current->next_;
  for (int i = 0; i < this->lenght_ && next != nullptr; i++){
    current->free();
    current = next;
    next = next->next_; 
  }

  current->free();
  this->lenght_ = 0;
  this->head_ = nullptr;
  this->tail_ = nullptr;
  
  delete this;

  return kErrorCode_Ok;
}

s16 List::softReset()
{
  if (this == nullptr)
    return kErrorCode_NULL;
  
  MemoryNode *current = this->head_;

  while (current != nullptr)
  {
    current->softFree();
    current = current->next_;
  }

  this->lenght_ = 0;
  
  return kErrorCode_Ok;
}

s16 List::reset()
{
  if (this == nullptr)
    return kErrorCode_NULL;

  if (this->isEmpty())
    return kErrorCode_Ok;
  
  MemoryNode *current = this->head_;
  MemoryNode *next = this->head_->next_;

  while (current != nullptr)
  {
    current->free();
    current = next;
    if (next != nullptr)
      next = next->next_;
  }

  this->lenght_ = 0;
  this->head_ = nullptr;
  this->tail_ = nullptr;
  return kErrorCode_Ok;
}

s16 List::resize(u16 new_size){
  if (this == nullptr)
    return kErrorCode_NULL;

  MemoryNode *current = new MemoryNode;
  while (this->lenght_ > new_size)
  {
    current->data_ = this->extractLast(nullptr);
    current->reset();

  }

  current->free();
  this->capacity_ = new_size;
  
  return kErrorCode_Ok;
}

u16 List::capacity()
{
  if (this == nullptr)
    return 0;
  return this->capacity_;
}

u16 List::length()
{
  if (this == nullptr)
    return 0;
  return this->lenght_;
}

boolean List::isEmpty()
{
  if (this == nullptr)
    return False;
  return (this->lenght_ == 0);
}

boolean List::isFull()
{
  if (this == nullptr)
    return True;
  return (this->lenght_ == this->capacity_);
}

void* List::first()
{
  if (this == nullptr)
    return nullptr;
  
  return this->head_;
}

void* List::last()
{
  if (this == nullptr)
    return nullptr;
  
  return this->tail_;
}

void* List::at(u16 position, u16 *size)
{
  if (this == nullptr)
    return nullptr;

  MemoryNode *current = this->head_;

  if (position > this->lenght_)
    return this->tail_;
  
  for (u16 i = 0; i < position; i++)
  {
    current = current->next_;
  }
  if (size != nullptr) *size = current->size_;
  return current->data_;
}

s16 List::insertFirst(void* data, u16 bytes)
{
  if (this == nullptr)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == nullptr)
    return kErrorCode_DataNULL;

  if (this->isFull())
    return kErrorCode_ListFull;
  
  MemoryNode *new_node = new MemoryNode();
  if (new_node == nullptr)
    return kErrorCode_NoMemory;

  new_node->setData(data, bytes);
  
  
  new_node->next_ = this->head_;
  this->head_ = new_node;

  if (this->tail_ == nullptr){
    this->tail_ = new_node;
  }
  
  this->lenght_++;
  
  return kErrorCode_Ok;
}

s16 List::insertLast(void* data, u16 bytes)
{
  if (this == nullptr)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == nullptr)
    return kErrorCode_DataNULL;

  if (this->isFull())
    return kErrorCode_ListFull;
  
  MemoryNode *new_node = new MemoryNode();
  if (new_node == nullptr)
    return kErrorCode_NoMemory;
  new_node->setData(data, bytes);

  
  // Si la lista esta vacia
  if (this->tail_ == nullptr)
  {
    new_node->next_ = nullptr;
    this->head_ = new_node;
    this->tail_ = new_node;
    
    // Si tiene cosas dentro
  }else{
    this->tail_->next_ = new_node;
    this->tail_ = new_node;
  }
    

  this->lenght_++;
  
  return kErrorCode_Ok;
}

s16 List::insertAt(void* data, u16 bytes, u16 position)
{
  if (this == nullptr)
    return kErrorCode_NULL;

  if (bytes == 0)
    return kErrorCode_ZeroBytes;

  if (data == nullptr)
    return kErrorCode_DataNULL;

  if (this->isFull())
    return kErrorCode_ListFull;

  if (this->isEmpty() || position == 0) {
    return this->insertFirst(data,bytes);
  }
  
  if (position > this->lenght_) {
    return this->insertLast(data, bytes);
  }

  MemoryNode *new_node = new MemoryNode();
  if (new_node == nullptr)
    return kErrorCode_NoMemory;
  new_node->setData(data, bytes); 

  MemoryNode *current = this->head_;
  for (s16 i = 0; i < position - 1; i++)
  {
    current = current->next_;
  }

  if (current != nullptr)
  {
    new_node->next_ = current->next_;
    current->next_ = new_node;
    
  }
  else
  {
    new_node->next_ = nullptr;
    this->head_ = new_node;
    this->tail_ = new_node;
  }

  this->lenght_++;
  
  return kErrorCode_Ok;
}

void* List::extractFirst()
{
  if (this == nullptr)
    return nullptr;

  MemoryNode *extract_node = this->head_;
  void* extract_data;
  if (extract_node != nullptr)
  {
    this->head_ = extract_node->next_;
    if (this->lenght_ == 1){
      this->tail_ = nullptr;
      this->head_ = nullptr;
    }
    
    this->lenght_--;
    extract_data = extract_node->data_;
    extract_node->softFree();
    return extract_data;
  }
  
  return nullptr;
}

void* List::extractLast(u16* size)
{
  if (this == nullptr)
    return nullptr;
  
  MemoryNode *current = this->head_;
  if (current == nullptr)
    return nullptr;

  if (this->lenght_ == 1){
    // only one node in the list
    this->head_ = nullptr;
    this->tail_ = nullptr;
  }else{
    // more than one node in the list
    // Llegamos hasta el penultimo
    u32 index_debug = 0;
    while (current->next_->next_ != nullptr)
    {
      index_debug++;
      current = current->next_;
    }
    this->tail_ = current;
    current = current->next_;
    this->tail_->next_ = nullptr;
  }
  this->lenght_--;
  if (size != nullptr) *size = current->size_;
  void *data_tmp = current->data_;
  current->softFree();
  return data_tmp;
}

void* List::extractAt(u16 position)
{
  if (this == nullptr)
    return nullptr;
  if (position == 0) {
    return this->extractFirst();
  }

  if (this->lenght_ < position)
    position = this->lenght_;
  
  MemoryNode *current = this->head_;
  for (s16 i = 0; i < position - 1; i++)
  {
    current = current->next_;
  }

  MemoryNode *extract_node = current->next_;
  if (extract_node != nullptr)
    current->next_ = extract_node->next_;
  else
    current->next_ = nullptr;
  
  
  if (extract_node != nullptr)
  {
    this->lenght_--;
    void *data = extract_node->data_;
    extract_node->softFree();
    return data;
  }
  
  return nullptr;
}

s16 List::concat(List* list_src)
{
  if (this == nullptr || list_src == nullptr)
    return kErrorCode_NULL;

  u32 new_capacity = this->capacity_ + list_src->capacity_;

  this->resize(new_capacity);

  MemoryNode *copy_node = new MemoryNode();
  MemoryNode *current = new MemoryNode();
  for (u32 i = 0; i < list_src->lenght_; i++)
  {
    current->data_ = list_src->at(i, &current->size_);
    copy_node->memCopy(current->data_, current->size_);
    this->insertLast(copy_node->data_, copy_node->size_);
    copy_node->softReset();
  }
  
  copy_node->softFree();
  current->softFree();
  
  return kErrorCode_Ok;
}

s16 List::traverse(void (* callback)(MemoryNode*))
{
  if (this == nullptr)
    return kErrorCode_NULL;

  if (callback == nullptr)
    return kErrorCode_CallBackNULL;
  
  MemoryNode *current  = this->head_;
  for (u16 i = 0; i < this->lenght_; i++)
  {
    callback(current);
    current = current->next_;
  }
  
  return kErrorCode_Ok;
}

void List::print()
{
  if (this == nullptr)
    return;
  
  MemoryNode *current  = this->head_;
  for (u16 i = 0; i < this->lenght_ && current != nullptr; i++)
  {
    current->print();
    current = current->next_;
  }
}

void* List::operator new(size_t count)
{
  return MM->malloc(count);
}

void List::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* List::operator new [](size_t count)
{
  return MM->malloc(count);
}

void List::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}







