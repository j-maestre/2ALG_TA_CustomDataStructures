#include "vector.h"

#include <algorithm>

#include "common_def.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

Vector::Vector() : head_(0), tail_(0), capacity_(0), storage_(nullptr)
{
  
}

Vector::Vector(const Vector& other) : Vector()
{
  this->head_ = other.head_;
  this->tail_ = other.tail_;
  this->capacity_ = other.capacity_;

  if (this->capacity_ > 0)
  {
    this->storage_ = new MemoryNode[this->capacity_];
    for (u16 i = 0; i < this->capacity_; i++)
    {
      this->storage_[i] = other.storage_[i];
    }
  }
}

Vector::Vector(Vector&& other)
{
  this->head_ = other.head_;
  this->tail_ = other.tail_;
  this->capacity_ = other.capacity_;
  this->storage_ = other.storage_;
  other.storage_ = nullptr;
}

Vector::~Vector()
{
  
}

Vector& Vector::operator=(const Vector& other)
{
  if (this != &other)
  {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->capacity_ = other.capacity_;
    if (this->capacity_ > 0)
    {
      this->storage_ = new MemoryNode[this->capacity_];
      for (u16 i = 0; i < this->capacity_; i++)
      {
        this->storage_[i] = other.storage_[i];
      }
    }
  }
  
  return *this;
}

Vector& Vector::operator=(Vector&& other)
{
  if (this != &other)
  {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->capacity_ = other.capacity_;
    delete[] this->storage_;
    this->storage_ = other.storage_;
    other.storage_ = nullptr;
  }

  return *this;
}

Vector* Vector::Create()
{
  return new Vector();
}

s16 Vector::CreateFromRef(Vector** vector)
{
  if (nullptr == vector) {
    return kErrorCode_VectorNULL;
  }
  
  *vector = Vector::Create();
  if (*vector == nullptr)
  {
    return kErrorCode_NoMemory;
  }

  return kErrorCode_Ok;
}

s16 Vector::destroy()
{
  for (u16 i = 0; i < this->capacity_; i++)
  {
    this->storage_[i].reset();
  }
  delete[] this->storage_;
  delete this;
  
  return kErrorCode_Ok;
}

s16 Vector::softReset()
{
  if (this->storage_ == nullptr)
  {
    return kErrorCode_StorageNULL;
  }

  for (u16 i = 0; i < this->capacity_; i++)
  {
    this->storage_[i].softReset();
  }
  this->tail_ = 0;

  return kErrorCode_Ok;
}

s16 Vector::reset()
{
  if (this->storage_ == nullptr)
  {
    return kErrorCode_StorageNULL;
  }

  for (u16 i = 0; i < this->capacity_; i++)
  {
    this->storage_[i].reset();
  }
  this->tail_ = 0;

  return kErrorCode_Ok;
}

s16 Vector::resize(u16 new_size)
{
  if(new_size == 0){
    return kErrorCode_SizeZERO;
  }

  if( new_size == this->capacity_){
    return kErrorCode_Ok;
  }

  MemoryNode *node_tmp = new MemoryNode[new_size];
  if (node_tmp == nullptr)
  {
    return kErrorCode_NoMemory;
  }

  if(new_size > this->capacity_){
    // Al alza
    for (u32 i = 0; i < this->tail_; i++){
      node_tmp[i] = std::move(this->storage_[i]);
    }

  }else
  {
    // A la baja
    for (u32 i = 0; i < this->tail_; i++){

      if(i<new_size){
        node_tmp[i] = std::move(this->storage_[i]);
      }else{
        this->storage_[i].reset();
      }
    }
  }
  
  delete[] this->storage_;
  this->storage_ = node_tmp;
  this->capacity_ = new_size;

  if (this->tail_ > new_size)
  {
    this->tail_ = new_size;
  }

  return kErrorCode_Ok;
}

u16 Vector::capacity() const
{
  return this->capacity_;
}

u16 Vector::length() const
{
  if(this->tail_ > this->capacity_){
    return 0;
  }
  
  return this->tail_ - this->head_;
}

boolean Vector::isEmpty() const
{
  if(this->tail_ == 0){
    return True;
  }

  return False;
}

boolean Vector::isFull() const
{
  return (this->tail_ == this->capacity_);
}

void* Vector::first()
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  return this->storage_->data_;
}

void* Vector::last()
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  u32 offset = 0;
  if(this->tail_ > 0){
    offset = this->tail_ -1;
  } else {
    return nullptr;
  }
  return (this->storage_ + offset)->data_;
}

void* Vector::at(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  if(position >= this->tail_){
    return nullptr;
  }
  return (this->storage_ + position)->data_;
}

s16 Vector::insertFirst(void* data, u16 bytes)
{
  if( nullptr == data){
    return kErrorCode_DataNULL;
  }
  if (nullptr == this->storage_) {
    return kErrorCode_StorageNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if (this->isFull())
  {
    return kErrorCode_VectorFull;
  }

  if (!this->isEmpty())
  {
    for (u32 i = this->tail_; i > 0 ; i--){
      this->storage_[i].setData(this->storage_[i-1].data_, this->storage_[i-1].size_);
    }
  }
  this->storage_->setData(data, bytes);
  this->tail_++;

  return kErrorCode_Ok;
}

s16 Vector::insertLast(void* data, u16 bytes)
{
  if (nullptr == this->storage_) {
    return kErrorCode_StorageNULL;
  }
  if( nullptr == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if(this->isFull()){
    this->storage_[this->tail_].setData(data, bytes);
    this->tail_++;
    return kErrorCode_Ok;
  }

  return kErrorCode_VectorFull;
}

s16 Vector::insertAt(void* data, u16 bytes, u16 position)
{
  if (nullptr == this->storage_) {
    return kErrorCode_StorageNULL;
  }
  if(nullptr == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if( position > this->tail_){
    position = this->tail_;
  }

  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  if(this->isEmpty()){
    // El vector tiene cosas, hay que moverlas
    for (u32 i = this->tail_; i > position ; i--){
      this->storage_[i].setData(this->storage_[i-1].data_, this->storage_[i-1].size_);
    }
    
  }

  this->storage_[position].setData(data, bytes);
  this->tail_++;
  
  return kErrorCode_Ok;
}

void* Vector::extractFirst()
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }

  //Reservamos el primer data
  void *data_tmp = (this->storage_)->data_;

  if(this->tail_ > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda
    for (u32 i = 0; i < this->tail_; i++){
      this->storage_[i].setData(this->storage_[i+1].data_, this->storage_[i+1].size_);
    }
    this->storage_[this->tail_-1].softReset();
  }

  this->tail_--;
  return data_tmp;
}

void* Vector::extractAt(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(position > this->tail_){
    return nullptr;
  }

  //Reservamos el primer data
  void *data_tmp = (this->storage_ + position)->data_;

  if(this->tail_ > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda
    for (u32 i = position; i < this->tail_; i++){
      this->storage_[i].setData(this->storage_[i+1].data_, this->storage_[i+1].size_);
    }
    this->storage_[this->tail_-1].softReset();
  }

  this->tail_--;
  return data_tmp;
}

void* Vector::extractLast()
{
  if( nullptr == (this->storage_)+(this->tail_)){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }

  void *data_tmp = ((this->storage_)+(this->tail_ - 1))->data_;
  this->storage_[this->tail_-1],softReset();
  this->tail_--;

  return data_tmp;
}

s16 Vector::concat(Vector* vector_src)
{
  if( nullptr == vector_src){
    return kErrorCode_VectorNULL;
  }

  if( nullptr == this->storage_ || nullptr == vector_src->storage_){
    return kErrorCode_StorageNULL;
  }

  MemoryNode *node = new MemoryNode[this->capacity_ + vector_src->capacity_];
  if (NULL == node) {
    return kErrorCode_NoMemory;
  }
  
  for (u32 i = 0; i < this->tail_; i++){
    node[i].setData(this->storage_[i].data_, this->storage_[i].size_);
  }

  for (u32 i = 0; i < vector_src->tail_; i++){
    node[i + this->tail_].memCopy(vector_src->storage_[i].data_, vector_src->storage_[i].size_);
  }

  delete[] this->storage_;
  this->storage_ = node;
  this->capacity_ = this->capacity_ + vector_src->capacity_;
  this->tail_ = this->tail_ + vector_src->tail_;

  return kErrorCode_Ok;
}

s16 Vector::traverse(void (* callback)(MemoryNode*))
{
  if( nullptr == callback){
    kErrorCode_CallBackNULL;
  }
  if( nullptr == this->storage_){
    return kErrorCode_StorageNULL;
  }

  for (u32 i = 0; i < this->capacity_; i++){
    callback((this->storage_+i));
  }

  return kErrorCode_Ok;
}

void Vector::print()
{
  if( nullptr == this->storage_){
    return;
  }

  printf("[VECTOR INFO] Address: %p\n",this);
  printf("[VECTOR INFO] Head: %d\n",this->head_);
  printf("[VECTOR INFO] Tail: %d\n",this->tail_);
  printf("[VECTOR INFO] Lenght: %d\n",this->tail_);
  printf("[VECTOR INFO] Capacity: %d\n",this->capacity_);
  printf("[VECTOR INFO] Address: %p\n",this->storage_);
  for(u32 i = 0; i < this->tail_; i++){
    printf("\t[VECTOR INFO] Storage #%d:\n",i);
    this->storage_[i].print();
  }
}

void* Vector::operator new(size_t count)
{
  return MM->malloc(sizeof(Vector));
}

void Vector::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* Vector::operator new [](size_t count)
{
  return MM->malloc(sizeof(Vector) * count);
}

void Vector::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}



