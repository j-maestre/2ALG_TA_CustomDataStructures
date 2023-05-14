#include "circular_vector.h"

#include <algorithm>

#include "common_def.h"
#include "vector.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

CircularVector::CircularVector(u16 size) : head_(0), tail_(0), capacity_(size), storage_(nullptr)
{
  storage_ = new MemoryNode[size];
}

CircularVector::CircularVector(const CircularVector& other) : CircularVector(other.capacity_)
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

CircularVector::CircularVector(CircularVector&& other)
{
  this->head_ = other.head_;
  this->tail_ = other.tail_;
  this->capacity_ = other.capacity_;
  this->storage_ = other.storage_;
  other.storage_ = nullptr;
}

CircularVector::~CircularVector()
{
  
}

CircularVector& CircularVector::operator=(const CircularVector& other)
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

CircularVector& CircularVector::operator=(CircularVector&& other)
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

CircularVector* CircularVector::Create(u16 size)
{
  if (size <= 0) return nullptr;
  return new CircularVector(size);
}

s16 CircularVector::destroy()
{
  for (u16 i = 0; i < this->capacity_; i++)
  {
    this->storage_[i].reset();
  }
  delete[] this->storage_;
  delete this;
  
  return kErrorCode_Ok;
}

s16 CircularVector::softReset()
{
  if (this->storage_ == nullptr)
  {
    return kErrorCode_StorageNULL;
  }

  for (u16 i = 0; i < this->length(); i++)
  {
    this->storage_[(this->head_ + i)%this->capacity_].softReset();
  }
  this->tail_ = 0;

  return kErrorCode_Ok;
}

s16 CircularVector::reset()
{
  if (this->storage_ == nullptr)
  {
    return kErrorCode_StorageNULL;
  }

  for (u16 i = 0; i < this->length(); i++)
  {
    this->storage_[(this->head_ + i)%this->capacity_].reset();
  }
  this->tail_ = 0;

  return kErrorCode_Ok;
}

s16 CircularVector::resize(u16 new_size)
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

  u16 size;
  MemoryNode *current_dst = node_tmp;
  u16 length = this->length();
  u16 index_aux = 0;

  for (int i = 0; i < this->capacity_; i++)
  {
    if (i < new_size)
    {
      void *data = this->extractFirst(&size);
      current_dst->setData(data, size);

      current_dst++;
    }
    else
    {
      this->storage_[(this->head_ + index_aux)%this->capacity_].reset();
      index_aux++;
    }
  }
  
  delete[] this->storage_;
  this->storage_ = node_tmp;
  this->capacity_ = new_size;
  this->head_ = 0;
  
  if (length < new_size)
    this->tail_ = length % new_size;
  else
    this->tail_ = new_size % new_size;

  return kErrorCode_Ok;
}

u16 CircularVector::capacity() const
{
  return this->capacity_;
}

u16 CircularVector::length() const
{
  if(this->tail_ > this->head_){
    return this->tail_ - this->head_;

  }else if(this->tail_ < this->head_){
    return (this->capacity_ - this->head_) + this->tail_;
  }else{

    // If head == tail
    if((this->storage_+this->head_)->data_ == nullptr){
      return 0;
    }else{
      return this->capacity_;
    }

  }
}

boolean CircularVector::isEmpty() const
{
  return this->length() == 0;
}

boolean CircularVector::isFull() const
{
  return (this->length() == this->capacity_);
}

void* CircularVector::first()
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  return (this->storage_ + this->head_)->data_;
}

void* CircularVector::last()
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  u16 index = this->tail_;

  if (index == 0) {
    index = this->capacity_;
  }
  return (this->storage_ + (index - 1))->data_;
}

void* CircularVector::at(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  return this->storage_[(this->head_ + position)%this->capacity_].data_;
}

s16 CircularVector::insertFirst(void* data, u16 bytes)
{
  if( nullptr == this->storage_){
    return kErrorCode_StorageNULL;
  }
  if( nullptr == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  //if(!CVECTOR_isEmpty(vector)){

  if(this->head_ == 0){
    this->head_ = this->capacity_;
  }
    
  this->head_--;
  //}

  this->storage_[this->head_].setData(data, bytes);
 
  return kErrorCode_Ok;
}

s16 CircularVector::insertLast(void* data, u16 bytes)
{
  if( nullptr == this->storage_){
    return kErrorCode_StorageNULL;
  }
  if( nullptr == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  this->storage_[this->tail_].setData(data, bytes);
  this->tail_ = (this->tail_ + 1) % (this->capacity_);

  return kErrorCode_Ok;
}

s16 CircularVector::insertAt(void* data, u16 bytes, u16 position)
{
  if( nullptr == this->storage_){
    return kErrorCode_StorageNULL;
  }
  if( nullptr == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  // TODO optimizar esto

  // Esta vacio, lo metemos al principio y au
  if(this->isEmpty()){
    this->storage_[this->head_].setData(data, bytes);
    this->tail_ = (this->tail_+1) % (this->capacity_);
    return kErrorCode_Ok;
  }

  // Se ha pasado del tail, lo metemos al final y au
  if(position > this->length()){

    this->storage_[this->tail_].setData(data, bytes);
    this->tail_ = (this->tail_+1) % (this->capacity_);
    return kErrorCode_Ok;
  }

  //Si esta al principio
  if(position == 0){

    if(this->head_ == 0){
      this->head_ = this->capacity_;
    }
    
    this->head_--;

    this->storage_[this->head_].setData(data, bytes);
    return kErrorCode_Ok;
  }

  // Fin optimizar


  MemoryNode *current_src = this->storage_;
  MemoryNode *current_dst = this->storage_;
  
  u16 index_dst = this->tail_;
  u16 index_src = this->tail_ - 1;
  u16 real_position = (this->head_+position) % this->capacity_;
  if(this->tail_ == 0){
    index_src = this->capacity_ - 1;
  }
  
  while(index_dst != real_position){

    (current_dst+index_dst)->setData((current_src + index_src)->data_, (current_src+index_src)->size_);

    index_dst--;
    index_src--;

    if(index_dst < 0){
      index_dst = this->capacity_-1;
    }
    if(index_src < 0){
      index_src == this->capacity_-1;
    }
    
  }


  (current_dst + real_position)->setData(data, bytes);
  this->tail_ = (this->tail_ + 1) % (this->capacity_);

  return kErrorCode_Ok;
}

void* CircularVector::extractFirst(u16 *size)
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->isFull()){
    return nullptr;
  }

  void *data_tmp = (this->storage_ + this->head_)->data_;

  this->storage_[this->head_].softReset();
  this->head_ = (this->head_+1) % (this->capacity_);

  return data_tmp;
}

void* CircularVector::extractAt(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }

  if(position >= this->length()){
    return nullptr;
  }

  //Reservamos el data seleccionado
  void *data_tmp = (this->storage_ + ((this->head_ + position)%this->capacity_))->data_;
  MemoryNode *current_src = this->storage_;
  MemoryNode *current_dst = this->storage_;

  

  u16 real_position = (this->head_ + position)%this->capacity_;
  u16 index_dst = real_position;
  u16 index_src = (real_position+1)%this->capacity_;


  while(index_src != this->tail_){
    (current_dst+index_dst)->setData((current_src + index_src)->data_, (current_src+index_src)->size_);

    index_dst = (index_dst+1)%this->capacity_;
    index_src = (index_src+1)%this->capacity_;

  }

  if(this->tail_ == 0){
    this->tail_ = this->capacity_;
  }

  this->tail_--;

  this->storage_[this->tail_].softReset();

  return data_tmp;
}

void* CircularVector::extractLast()
{
  if( nullptr == (this->storage_)+ (this->tail_ - 1)){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }


  
  if(this->tail_ == 0){
    this->tail_ = this->capacity_;
  }

  this->tail_--;
  
  void *data = (this->storage_ + (this->tail_))->data_;

  this->storage_[this->tail_].softReset();

  return data;
}

s16 CircularVector::concat(CircularVector* vector_src)
{
  if( nullptr == vector_src){
    return kErrorCode_VectorNULL;
  }

  if( nullptr == this->storage_ || nullptr == vector_src->storage_){
    return kErrorCode_StorageNULL;
  }

  

  u16 real_new_size = (this->capacity_ + vector_src->capacity_);
  s16 length = this->length() + vector_src->length();

  // Reservamos nuevo vector con el tamano de los dos
  MemoryNode *node = new MemoryNode[real_new_size];
  if (nullptr == node) {
    return kErrorCode_NoMemory;
  }

  //Primero sacar cuanto tenemos que meter sumando los dos vectores
  //Luego sacar la primera posicion donde tenemos que empezar a meter

  s16 new_head = 0;
  s16 new_tail = length;

  MemoryNode *current_dst = node;
  MemoryNode *current_src = this->storage_;
  //MemoryNode *end = vector->storage_ + vector->tail_;

  u16 index_dst = new_head;
  u16 index_src = this->head_;

  if(!this->isEmpty()){
    do {
      (current_dst + index_dst)->setData((current_src + index_src)->data_, (current_src + index_src)->size_);
      (current_src + index_src)->softReset();

      index_dst = (index_dst+1)%real_new_size;
      index_src = (index_src+1)%this->capacity_;
    
    } while (index_src != this->tail_);
  }

  current_src = vector_src->storage_;

  index_src = vector_src->head_;

  if(!vector_src->isEmpty()){
    do{
      current_dst[index_dst].memCopy((current_src + index_src)->data_, (current_src + index_src)->size_);
      //(current_src + index_src)->ops_->softReset((current_src + index_src));

      index_dst = (index_dst+1)%real_new_size;
      index_src = (index_src+1)%this->capacity_;
    }while(index_src != vector_src->tail_);

  }


  delete[] this->storage_;
  this->storage_ = node;
  this->capacity_ = real_new_size;
  this->tail_ = new_tail;
  this->head_ = new_head;

  return kErrorCode_Ok;
}

s16 CircularVector::traverse(void (* callback)(MemoryNode*))
{
  if( NULL == callback){
    return kErrorCode_CallBackNULL;
  }
  if( NULL == (this->storage_ + this->head_)){
    return kErrorCode_StorageNULL;
  }

  for (u32 i = this->head_; i != this->tail_; i = (i+1)%this->capacity_){
    callback((this->storage_+i));
  }

  return kErrorCode_Ok;
}

MemoryNode* CircularVector::data()
{
  return storage_;
}


void CircularVector::print()
{
  if( nullptr == (this->storage_ + this->head_)){
    return;
  }

  printf("[CVECTOR INFO] Address: %p\n",this);
  printf("[CVECTOR INFO] Head: %d\n",this->head_);
  printf("[CVECTOR INFO] Tail: %d\n",this->tail_);
  printf("[CVECTOR INFO] Lenght: %d\n",this->length());
  printf("[CVECTOR INFO] Capacity: %d\n",this->capacity_);
  printf("[CVECTOR INFO] Address: %p\n",this->storage_);

  for(u32 i = this->head_; i < this->tail_; i++){
    printf("\t[CVECTOR INFO] Storage #%d:\n",i);
    (this->storage_+i)->print();
  }
}

void* CircularVector::operator new(size_t count)
{
  return MM->malloc(count);
}

void CircularVector::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* CircularVector::operator new [](size_t count)
{
  return MM->malloc(count);
}

void CircularVector::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}