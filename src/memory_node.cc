#include "memory_node.h"

#include <cstdio>

#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

MemoryNode::MemoryNode() : data_(nullptr), size_(0), next_(nullptr), previous_(nullptr) {}

MemoryNode::MemoryNode(const MemoryNode& other) : MemoryNode()
{
  if (size_ > 0)
  {
    this->data_ = MM->malloc(other.size_);
    memCopy(other.data_, other.size_);
  }
  
  this->size_ = other.size_;
  this->next_ = other.next_;
  this->previous_ = other.previous_;
}

MemoryNode::MemoryNode(MemoryNode&& other)
{
  this->data_ = other.data_;
  this->size_ = other.size_;
  this->next_ = other.next_;
  this->previous_ = other.previous_;
  other.data_ = nullptr;
}

MemoryNode::~MemoryNode() {}

MemoryNode& MemoryNode::operator=(const MemoryNode& other)
{
   if (this != &other)
   {
     if (size_ > 0)
     {
       this->data_ = MM->malloc(other.size_);
       memCopy(other.data_, other.size_);
     }

     this->size_ = other.size_;
     this->next_ = other.next_;
     this->previous_ = other.previous_;
   }

  return *this;
}

MemoryNode& MemoryNode::operator=(MemoryNode&& other)
{
  if (this != &other)
  {
    this->data_ = other.data_;
    this->size_ = other.size_;
    this->next_ = other.next_;
    this->previous_ = other.previous_;
    other.data_ = nullptr;
  }
  
  return *this;
}

void* MemoryNode::operator new(size_t count)
{
  MemoryNode *aux = (MemoryNode*)MM->malloc(count);
  return aux;
}

void MemoryNode::operator delete(void* ptr)
{
  MemoryNode *aux = (MemoryNode*)ptr;
  MM->free(aux);
}

void* MemoryNode::operator new [](size_t count)
{
  MemoryNode *aux = (MemoryNode*)MM->malloc(count);
  return aux;
}

void MemoryNode::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}

MemoryNode* MemoryNode::Create()
{
  return new MemoryNode();
}

s16 MemoryNode::CreateFromRef(MemoryNode **node)
{
  if (NULL == node) {
    return kErrorCode_MemoryNodeNULL;
  }
  
  *node = MemoryNode::Create();
  if (*node == nullptr)
  {
    return kErrorCode_NoMemory;
  }

  return kErrorCode_Ok;
}


void* MemoryNode::data()
{
  return this->data_;
}

s16 MemoryNode::setData(void* src, u16 bytes)
{
  if (0 == bytes) {
    return kErrorCode_ZeroBytes;
  }
  
  if (NULL == src) {
    return kErrorCode_NULL;
  }

  this->data_ = src;
  this->size_ = bytes;

  return kErrorCode_Ok;
}

s16 MemoryNode::setNext(MemoryNode* next_node)
{
  this->next_ = next_node;

  return kErrorCode_Ok;
}

s16 MemoryNode::setPrevious(MemoryNode* previous_node)
{
  this->previous_ = previous_node;

  return kErrorCode_Ok;
}

u16 MemoryNode::size()
{
  return this->size_;
}

s16 MemoryNode::reset()
{
  if (nullptr != this->data_)
  {
    MM->free(this->data_);
  }

  this->data_ = nullptr;
  this->size_ = 0;
  
  return kErrorCode_Ok;
}

s16 MemoryNode::softReset()
{
  this->data_ = nullptr;
  this->size_ = 0;
  
  return kErrorCode_Ok;
}

s16 MemoryNode::free()
{
  if (this->data_ != nullptr)
  {
    MM->free(this->data_);
    this->data_ = nullptr;
  }

  delete this;

  return kErrorCode_Ok;
}

s16 MemoryNode::softFree()
{
  delete this;
  
  return kErrorCode_Ok;
}

s16 MemoryNode::memSet(u8 value)
{
  u8 *aux = (u8*)this->data_;

  for (u32 i = 0; i < this->size_; i++)
  {
    aux[i] = value;
  }

  return kErrorCode_Ok;
}

s16 MemoryNode::memCopy(void* src, u16 bytes)
{
  if( NULL == src){
    return kErrorCode_NULL;
  }

  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }
  if (NULL != this->data_) {
    MM->free(this->data_);
  }
  this->data_ = MM->malloc(bytes);

  if( NULL == this->data_){
    return kErrorCode_NoMemory;
  }

  this->size_ = bytes;

  u8 *aux = (u8 *) this->data_;
  u8 *aux2 = (u8 *) src;

  for (u32 i = 0; i < this->size_; i++){
    aux[i] = aux2[i];
  }
  
  return kErrorCode_Ok;
}

s16 MemoryNode::memConcat(void* src, u16 bytes)
{
  if( NULL == src){
    return kErrorCode_NULL;
  }

  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if (NULL == this->data_) {
    return kErrorCode_DataNULL;
  }

  u16 totalBytes = this->size_ + bytes;
  u8 *totalBlock = (u8 *) MM->malloc(totalBytes);
  if (NULL == totalBlock){
    return kErrorCode_NoMemory;
  }
  u8 *aux = (u8 *) this->data_;

  for(u32 i = 0; i < this->size_; i++){
    totalBlock[i] = aux[i];
  }

  aux = (u8 *) src;

  for(u32 i = this->size_; i < totalBytes; i++){
    totalBlock[i] = aux[i - this->size_];
  }

  MM->free(this->data_);
  this->data_ = (void *)totalBlock;
  this->size_ = totalBytes;

  return kErrorCode_Ok;
}

s16 MemoryNode::memMask(u8 mask)
{
  if (NULL == this->data_) {
    return kErrorCode_DataNULL;
  }


  u8 *aux = (u8 *) this->data_;

  for (u32 i = 0; i < this->size_; i++){
    aux[i] &= mask;
  }
  
  return kErrorCode_Ok;
}

void MemoryNode::print()
{
  printf("[Node Info] Adress: %p\n", this);
  printf("[Node Info] Size: %d\n", this->size_);
  if( NULL != this->data_)printf("[Node Info] Data address: %p\n", this->data_);
  printf("[Node Info] content: ");
  for (u32 i = 0; i < this->size_; i++){
    if (this->data_ != NULL)
    {
      printf("%c",((u8 *) this->data_)[i]);
    }
  }
  printf("\n");
}






