#include "movable_vector.h"

#include <cstdio>

#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

MVector::MVector(u16 size) : tail_(0), head_(0), capacity_(size), storage_(nullptr)
{
  storage_ = new MemoryNode[capacity_];
}

MVector::MVector(const MVector& other) : MVector(other.capacity_)
{
  this->tail_ = other.tail_;
  this->head_ = other.head_;
  for (u16 i = 0; i < this->capacity_; i++)
  {
    this->storage_[i] = other.storage_[i];
  }
}

MVector::MVector(MVector&& other)
{
  this->tail_ = other.tail_;
  this->head_ = other.head_;
  this->capacity_ = other.capacity_;
  this->storage_ = other.storage_;
  other.storage_ = nullptr;
}

MVector::~MVector()
{
  
}

MVector& MVector::operator=(const MVector& other)
{
  if (this != &other)
  {
    this->tail_ = other.tail_;
    this->capacity_ = other.capacity_;
    this->head_ = other.head_;
    for (u16 i = 0; i < this->capacity_; i++)
    {
      this->storage_[i] = other.storage_[i];
    }
  }

  return *this;
}

MVector& MVector::operator=(MVector&& other)
{
  if (this != &other)
  {
    this->tail_ = other.tail_;
    this->head_ = other.head_;
    this->capacity_ = other.capacity_;
    this->storage_ = other.storage_;
    other.storage_ = nullptr;
  }

  return *this;
}

void* MVector::operator new(size_t count)
{
  return MM->malloc(count);
}

void MVector::operator delete(void* ptr)
{
  MM->free(ptr);
}

void* MVector::operator new [](size_t count)
{
  return MM->malloc(count);
}

void MVector::operator delete [](void* ptr, size_t count)
{
  MM->free(ptr);
}

MVector* MVector::Create(u16 size)
{
  return new MVector(size);
}

s16 MVector::destroy()
{
  if(nullptr != this->storage_){

    for (u32 i = this->head_; i < this->tail_; i++){
      (this->storage_+i)->reset();
    }
    delete[] this->storage_;

  }
  delete this;

  return kErrorCode_Ok;
}

s16 MVector::softReset()
{
  if( nullptr != this->storage_){  
    for (u32 i = this->head_; i < this->tail_; i++){
      (this->storage_+i)->softReset();
    }
    this->head_ = (this->capacity_ >> 1) - 1;
    this->tail_ = (this->capacity_ >> 1) - 1;
    return kErrorCode_Ok;    
  }

  return kErrorCode_StorageNULL;
}

s16 MVector::reset()
{
  if( nullptr != this->storage_){
    for (u32 i = this->head_; i < this->tail_; i++){
      (this->storage_+i)->reset();
    }
    this->head_ = (this->capacity_ >> 1) - 1;
    this->tail_ = (this->capacity_ >> 1) - 1;
    return kErrorCode_Ok;
  }

  return kErrorCode_StorageNULL;
}

s16 MVector::resize(u16 new_size)
{
  if(new_size == 0){
    return kErrorCode_SizeZERO;
  }

  s16 real_new_size = new_size << 1;

  if( real_new_size == this->capacity_){
    return kErrorCode_Ok;
  }

  MemoryNode *new_storage = new MemoryNode[real_new_size];
  if (new_storage == NULL){
    return kErrorCode_NoMemory;
  }


  MemoryNode *current_src = new_storage;
  MemoryNode *end = new_storage + real_new_size;

  s16 length = (this->tail_ - this->head_);

  if (length > new_size) {
    length = new_size;
  }

  s16 new_head = ((real_new_size - length) / 2);
  s16 new_tail = (new_head + length);

  MemoryNode *current_dst;

  if (real_new_size > this->capacity_) {
    // Al alza

    current_dst = new_storage + new_head;
    end = current_dst + (new_tail - new_head);
    current_src = this->storage_ + this->head_;

    do {
      current_dst->setData(current_src->data_, current_src->size_);
      current_dst++;
      current_src++;
    } while (current_dst != end);

  } else {
    // A la baja

    current_dst = new_storage + new_head;
    current_src = this->storage_ + this->head_;
    //end = vector->storage_ + vector->tail_;
    end = current_src + (this->tail_ - this->head_);
    MemoryNode *max_dst = current_dst + (new_size - 1);

    do {

      if (current_dst <= max_dst) {
        current_dst->setData(current_src->data_, current_src->size_);
      }else{
        current_src->reset();
      }
      
      current_dst++;
      current_src++;
    } while (current_src != end);

    if (new_tail > real_new_size) {
      new_tail = real_new_size;
    }
    
  }
  
  //MM->free(vector->storage_);
  delete[] this->storage_;
  this->storage_ = new_storage;
  this->capacity_ = real_new_size;
  this->tail_ = new_tail;
  this->head_ = new_head;

  return kErrorCode_Ok;
}

u16 MVector::capacity() const
{
  return this->capacity_ >> 1;
}

u16 MVector::length() const
{
  return this->tail_ - this->head_;
}

boolean MVector::isEmpty() const
{
  if(this->tail_ == this->head_){
    return True;
  }

  return False;
}

boolean MVector::isFull() const
{
  return ((this->tail_ - this->head_) >= (this->capacity_ >> 1));
}

void* MVector::first()
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  return (this->storage_ + this->head_)->data_;
}

void* MVector::last()
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->tail_ > this->head_){
    return (this->storage_ + (this->tail_ -1))->data_;
  } else {
    return nullptr;
  }
}

void* MVector::at(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }
  if(position >= (this->tail_ >> 1) || position < 0){
    return nullptr;
  }
  return (this->storage_ + (this->head_ + position))->data_;
}

void MVector::center()
{
  if(this->tail_ < this->capacity_){
    u16 mitad = this->capacity_ >> 1;
    u16 inicio = (this->tail_-1) >> 1;
    u16 new_head = mitad - inicio;
    u16 new_tail = new_head + (this->tail_ - this->head_);

    MemoryNode *aux;
    aux  = new MemoryNode[this->capacity_];
    u16 indexOriginal = this->head_;
    

    // Rellenamos el memnode auxiliar centrado con los valores del vector original
    for(u32 i = new_head; i < new_tail; i++){
      aux[i].setData((this->storage_ + indexOriginal)->data_,(this->storage_ + indexOriginal)->size_);
      indexOriginal++;
    }
    
    delete[] this->storage_;
    this->storage_ = aux;
    this->head_ = new_head;
    this->tail_ = new_tail;

  }
}

s16 MVector::insertFirst(void* data, u16 bytes)
{
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if (NULL == this->storage_) {
    return kErrorCode_StorageNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  //Comprobamos que head no esta al principio
  if(this->head_ == 0){
    //Si esta al principio y hay espacio, aprovechamos y lo centramos
    this->center();
  }

  u32 new_head = this->head_;
  if(!this->isEmpty()){
    new_head--;
  }else {
    this->tail_++;
  }
  

  //Metemos en head el nuevo data
  (this->storage_ + (new_head) )->setData(data,bytes);
  this->head_ = new_head;

  return kErrorCode_Ok;
}

s16 MVector::insertLast(void* data, u16 bytes)
{
  if (NULL == this->storage_) {
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if(this->isFull()){
    return kErrorCode_VectorFull;
  }

  if (this->tail_ >= this->capacity_) {
    this->center();
  }

  (this->storage_ + this->tail_)->setData(data, bytes);
  this->tail_++;
  return kErrorCode_Ok;
}

s16 MVector::insertAt(void* data, u16 bytes, u16 position)
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

  if (this->isEmpty()) {
    this->storage_[this->tail_].setData(data, bytes);
    this->tail_++;
    return kErrorCode_Ok;
  }

  if (this->isFull()) {
    return kErrorCode_VectorFull;
  }

  s32 real_position  = this->head_ + position;

  // Si la posicion es mayor que el tail, lo metemos al final y arreando
  if (real_position > this->tail_) {
    this->storage_[this->tail_].setData(data, bytes);
    this->tail_++;
    return kErrorCode_Ok;
  }

  s16 right_distance = (this->tail_ - 1) - real_position;
  s16 left_distance = real_position - this->head_;

  MemoryNode *destination = this->storage_ + real_position;

  MemoryNode *current_src;
  MemoryNode *current_dst;

  if (right_distance > left_distance) {
    //Move to left

    current_dst = (this->storage_ + (this->head_ - 1));
    current_src = (this->storage_ + this->head_);

    while (current_dst != destination) {
      current_dst->setData(current_src->data_, current_src->size_);
      current_dst++;
      current_src++;
    }
    
    this->head_--;

  } else {
    //Move to right

    current_dst = (this->storage_ + this->tail_);
    current_src = (this->storage_ + (this->tail_ - 1));

    while (current_dst != destination) {
      current_dst->setData(current_src->data_, current_src->size_);
      current_dst--;
      current_src--;
    }

    this->tail_++;

  }
  destination->setData(data, bytes);


  return kErrorCode_Ok;
}

void* MVector::extractFirst()
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->isEmpty()){
    return NULL;
  }

  //Reservamos el primer data
  void *data_tmp = (this->storage_ + this->head_)->data_;
  this->storage_[this->head_].softReset();
  this->head_++;

  return data_tmp;
}

void* MVector::extractAt(u16 position)
{
  if( nullptr == this->storage_){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }

  //if(position > (vector->head_ + vector->tail_)){
  if(position > (this->tail_ - this->head_) || position < 0){ // si la posicion esta fuera del rango
    return NULL;
  }

  //Reservamos el data seleccionado
  void *data_tmp = (this->storage_ + (this->head_ + position))->data_;

  if((this->tail_ - this->head_) > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda empezando por la position
    for (u32 i = position + this->head_; i < this->tail_; i++){
      ((this->storage_)+i)->setData(((this->storage_)+i+1)->data_,((this->storage_)+i+1)->size_);
    }

    //El ultimo elemento lo eliminamos porque esta duplicado
    (this->storage_+(this->tail_-1))->softReset();
  }

  this->tail_--;
  return data_tmp;
}

void* MVector::extractLast()
{
  if( nullptr == (this->storage_)+ (this->tail_ - 1)){
    return nullptr;
  }

  if(this->isEmpty()){
    return nullptr;
  }

  void *data = (this->storage_ + (this->tail_ - 1))->data_;
  this->tail_--;
  this->storage_[this->tail_].softReset();

  return data;
}

s16 MVector::concat(MVector* vector_src)
{
  if( NULL == vector_src){
    return kErrorCode_VectorNULL;
  }

  if( NULL == this->storage_ || NULL == vector_src->storage_){
    return kErrorCode_StorageNULL;
  }

  

  u16 real_new_size = (this->capacity_ + vector_src->capacity_);
  s16 length = ((this->tail_ - this->head_) + (vector_src->tail_ - vector_src->head_));

  // Reservamos nuevo vector con el tamano de los dos
  MemoryNode *node = new MemoryNode[real_new_size];
  if (NULL == node) {
    return kErrorCode_NoMemory;
  }  

  //Primero sacar cuanto tenemos que meter sumando los dos vectores
  //Luego sacar la primera posicion donde tenemos que empezar a meter

  s16 new_head = ((real_new_size - length) / 2);
  s16 new_tail = (new_head + length); // + 1 ???

  MemoryNode *current_dst = node + new_head;
  MemoryNode *current_src = this->storage_ + this->head_;
  MemoryNode *end = this->storage_ + this->tail_;

  if(!this->isEmpty()){
    do {
#ifdef VERBOSE_
      printf("\x1B[34m[VERBOSE_]\x1B[37m");
      printf("Moveing memory from 0x%p[0x%p] to 0x%p[0x%p]\n", current_src, current_src->data_, current_dst, current_dst->data_);
#endif
      current_dst->setData(current_src->data_, current_src->size_);
      current_src->softReset();
      current_dst++;
      current_src++;
    } while (current_src != end);
  }

  current_src = vector_src->storage_ + vector_src->head_;
  end = vector_src->storage_ + vector_src->tail_;

  if(!vector_src->isEmpty()){
    do{
#ifdef VERBOSE_
      printf("\x1B[34m[VERBOSE_]\x1B[37m");
      printf("Copying memory from 0x%p[0x%p] to 0x%p[0x%p]\n", current_src, current_src->data_, current_dst, current_dst->data_);
#endif
      current_dst->memCopy(current_src->data_, current_src->size_);
      current_dst++;
      current_src++;
    }while(current_src != end);

  }
  
  delete[] this->storage_;
  this->storage_ = node;
  this->capacity_ = real_new_size;
  this->tail_ = new_tail;
  this->head_ = new_head;

  return kErrorCode_Ok;
}

s16 MVector::traverse(void (* callback)(MemoryNode*))
{
  if( NULL == callback){
    return kErrorCode_CallBackNULL;
  }
  if( NULL == (this->storage_ + this->head_)){
    return kErrorCode_StorageNULL;
  }

  for (u32 i = this->head_; i < this->tail_; i++){
    callback((this->storage_+i));
  }

  return kErrorCode_Ok;
}

MemoryNode* MVector::data()
{
  return this->storage_;
}

void MVector::print()
{
  if( nullptr == (this->storage_ + this->head_)){
    return;
  }
  printf("[MVECTOR INFO] Address: %p\n",this);
  printf("[MVECTOR INFO] Head: %d / %d\n",this->head_, 0);
  printf("[MVECTOR INFO] Tail: %d / %d\n",this->tail_, this->tail_ - this->head_);
  printf("[MVECTOR INFO] Lenght: %d\n",this->tail_ - this->head_);
  printf("[MVECTOR INFO] Capacity: %d / %d\n",this->capacity_, this->capacity_ >> 1);
  printf("[MVECTOR INFO] Address: %p\n",this->storage_);

  for(u32 i = this->head_; i < this->tail_; i++){
    printf("\t[MVECTOR INFO] Storage #%d / #%d:\n",i, i - this->head_);
    (this->storage_+i)->print();
  }
}










