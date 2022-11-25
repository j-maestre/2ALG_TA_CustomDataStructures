#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 VECTOR_destroy(Vector *vector);
static s16 VECTOR_softReset(Vector *vector);
static s16 VECTOR_reset(Vector *vector);
static s16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_lenght(Vector *vector);
static boolean VECTOR_isEmpty(Vector *vector);
static boolean VECTOR_isFull(Vector *vector);
static void* VECTOR_first(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes);
static s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position);
static void* VECTOR_extractFirst(Vector *vector);
static void* VECTOR_extractLast(Vector *vector);
static void* VECTOR_extractAt(Vector *vector, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *vector_src);
static s16 VECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *));
static void VECTOR_print(Vector *vector);

struct vector_ops_s vector_ops = { .destroy = VECTOR_destroy,
                                   .softReset = VECTOR_softReset,
                                   .reset = VECTOR_reset,
                                   .resize = VECTOR_resize,
                                   .capacity = VECTOR_capacity,
                                   .length = VECTOR_lenght,
                                   .isEmpty = VECTOR_isEmpty,
                                   .isFull = VECTOR_isFull,
                                   .first = VECTOR_first,
                                   .last = VECTOR_last,
                                   .at = VECTOR_at,
                                   .insertFirst = VECTOR_insertFirst,
                                   .insertLast = VECTOR_insertLast,
                                   .insertAt = VECTOR_insertAt,
                                   .extractFirst = VECTOR_extractFirst,
                                   .extractLast = VECTOR_extractLast,
                                   .extractAt = VECTOR_extractAt,
                                   .concat = VECTOR_concat,
                                   .traverse = VECTOR_traverse,
                                   .print = VECTOR_print                   
                                   };

Vector* VECTOR_create(u16 capacity) {//checked
	if (0 >= capacity) {
		return NULL;
	}
	Vector* rslt = (Vector *)MM->malloc(sizeof(Vector));
	if (NULL == rslt) {
		return NULL;
	}
	rslt->storage_ = (MemoryNode *) MM->malloc(sizeof(MemoryNode) * capacity);
	if (NULL == rslt->storage_) {
		MM->free(rslt);
		return NULL;
	}
	for (u32 i = 0; i < capacity; i++) {
		MEMNODE_createLite((rslt->storage_ + i));
	}
	rslt->head_ = 0;
	rslt->tail_ = 0;
	rslt->capacity_ = capacity;
	rslt->ops_ = &vector_ops;
	return rslt;
}

s16 VECTOR_destroy(Vector *vector){ //checked
  if( NULL != vector){
    if(NULL != vector->storage_){

      for (u32 i = 0; i < vector->tail_; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+i));
      }
      MM->free(vector->storage_);

    }

    MM->free(vector);
  }

  return kErrorCode_Ok;
}

s16 VECTOR_softReset(Vector *vector){ //checked
  if( NULL != vector){
    if( NULL != vector->storage_){  
      for (u32 i = 0; i < vector->capacity_; i++){
        (vector->storage_+i)->ops_->softReset((vector->storage_+i));
      }
      vector->tail_ = 0;
      return kErrorCode_Ok;    
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}

s16 VECTOR_reset(Vector *vector){//checked
  if( NULL != vector){
    if( NULL != vector->storage_){
      for (u32 i = 0; i < vector->tail_; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+i));
      }
      vector->tail_ = 0;
      return kErrorCode_Ok;
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}

s16 VECTOR_resize(Vector *vector, u16 new_size){ //Checked
  if( NULL == vector){

    return kErrorCode_VectorNULL; 
  }

  if(new_size == 0){
    return kErrorCode_SizeZERO;
  }

  if( new_size == vector->capacity_){
    return kErrorCode_Ok;
  }

  MemoryNode *node_tmp = (MemoryNode*) MM->malloc(sizeof(MemoryNode)*new_size);
  if(node_tmp == NULL){
    return kErrorCode_NoMemory;
  }
  for (u32 i = 0; i < new_size; i++) {
    MEMNODE_createLite(node_tmp + i);
  }
  
  if(new_size > vector->capacity_){
    // Al alza
    for (u32 i = 0; i < vector->tail_; i++){

      (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));
    }

  }else{
    // A la baja
    for (u32 i = 0; i < vector->tail_; i++){

      if(i<new_size){
        (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));

      }else{
        (vector->storage_+i)->ops_->reset(vector->storage_ + i);
      }
    }




  }

  MM->free(vector->storage_);
  vector->storage_ = node_tmp;
  vector->capacity_ = new_size;
    
  if(vector->tail_ > new_size){
    vector->tail_ = new_size;
  }

  // new size == capacity
  return kErrorCode_Ok;
  
}

u16 VECTOR_capacity(Vector *vector){//checked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }

  return vector->capacity_;
}

u16 VECTOR_lenght(Vector *vector){//checked
  if( NULL == vector){
    //return kErrorCode_VectorNULL;
    return kErrorCode_Ok;
  }
  if(vector->tail_ > vector->capacity_){
    //return kErrorCode_VectorTailExceedsCapacity;
    return kErrorCode_Ok;
  }
  
  return vector->tail_;

}

boolean VECTOR_isEmpty(Vector *vector){//Checked
  if( NULL == vector){
    return False;
  }

  if(vector->tail_ == 0){
    return True;
  }

  return False;
}

boolean VECTOR_isFull(Vector *vector){//Checked
  if( NULL == vector){
    return False;
  }
  // En el caso de que cuando se añada el ultimo elemento, el tail sea +1 respecto a la capacidad
  return (vector->tail_ == vector->capacity_);
}

void* VECTOR_first(Vector *vector){//Checked

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  return vector->storage_->data_;

}

void* VECTOR_last(Vector *vector){//Checked

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  int offset = 0;
  if(vector->tail_ > 0){
    offset = vector->tail_ -1;
  } else {
    return NULL;
  }
  return (vector->storage_ + offset)->data_;
} 

void* VECTOR_at(Vector *vector, u16 position){//Checked

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  if(position >= vector->tail_){
    return NULL;
  }
  return (vector->storage_ + position)->data_;
}

s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes){//checked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  // Mover todo lo que haya una posicion a la izquierda en caso de que haya algo y no se pase
  if(VECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  if(!VECTOR_isEmpty(vector)){
    // El vector tiene cosas, hay que moverlas
    for (u32 i = vector->tail_; i > 0 ; i--){
      (((vector->storage_)+i)->ops_)->setData( ((vector->storage_)+i) , ((vector->storage_)+(i-1) )->data_, ((vector->storage_)+(i-1))->size_);
    }
    
  }
  (vector->storage_)->ops_->setData(vector->storage_,data, bytes);
  vector->tail_++;

  return kErrorCode_Ok;
} 

s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes){//cheked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if(!VECTOR_isFull(vector)){
    
    ((vector->storage_) + (vector->tail_))->ops_->setData((vector->storage_) + (vector->tail_),data,bytes);
    vector->tail_++;
    return kErrorCode_Ok;
  }

  return kErrorCode_VectorFull;
}

s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position){//cheked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if( position > vector->tail_){
    return kErrorCode_VectorPositionExceedsTail;
  }

  if(VECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  if(!VECTOR_isEmpty(vector)){
    // El vector tiene cosas, hay que moverlas
    for (u32 i = vector->tail_; i > position ; i--){
      (((vector->storage_)+i)->ops_)->setData( ((vector->storage_)+i) , ((vector->storage_)+(i-1) )->data_, ((vector->storage_)+(i-1))->size_);
    }
    
  }

  ((vector->storage_)+position)->ops_->setData(((vector->storage_)+position),data,bytes);


  if(position == vector->tail_){
    vector->tail_++;
  }

  return kErrorCode_Ok;
  
}

void* VECTOR_extractFirst(Vector *vector){//checked
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  if(VECTOR_isEmpty(vector)){
    return NULL;
  }

  //Reservamos el primer data
  void *data_tmp = (vector->storage_)->data_;

  if(vector->tail_ > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda
    for (u32 i = 0; i < vector->tail_; i++){
      ((vector->storage_)+i)->ops_->setData(((vector->storage_)+i),((vector->storage_)+i+1)->data_,((vector->storage_)+i+1)->size_);
    }
    (vector->storage_+(vector->tail_-1))->ops_->softReset(vector->storage_+(vector->tail_-1));
  }

  vector->tail_--;
  return data_tmp;
}

void* VECTOR_extractAt(Vector *vector, u16 position){//checked
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  if(position > vector->tail_){
    return NULL;
  }

  //Reservamos el primer data
  void *data_tmp = (vector->storage_ + position)->data_;

  if(vector->tail_ > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda
    for (u32 i = position; i < vector->tail_; i++){
      ((vector->storage_)+i)->ops_->setData(((vector->storage_)+i),((vector->storage_)+i+1)->data_,((vector->storage_)+i+1)->size_);
    }
    (vector->storage_+(vector->tail_-1))->ops_->softReset(vector->storage_+(vector->tail_-1));
  }

  vector->tail_--;
  return data_tmp;
}

void* VECTOR_extractLast(Vector *vector){//checked
  if( NULL == vector){
    return NULL;
  }
  if( NULL == (vector->storage_)+(vector->tail_)){
    return NULL;
  }

  if(VECTOR_isEmpty(vector)){
    return vector->storage_->data_;
  }

  void *data_tmp = ((vector->storage_)+(vector->tail_ - 1))->data_;
  vector->storage_->ops_->softReset((vector->storage_) + (vector->tail_ - 1));
  vector->tail_--;

  return data_tmp;
}

s16 VECTOR_concat(Vector *vector, Vector *vector_src){//checked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector_src){
    return kErrorCode_VectorNULL;
  }

  if( NULL == vector->storage_ || NULL == vector_src->storage_){
    return kErrorCode_StorageNULL;
  }


  MemoryNode *node = MM->malloc(sizeof(MemoryNode) * (vector->capacity_ + vector_src->capacity_));
  for (u32 i = 0; i < (vector->capacity_ + vector_src->capacity_); i++){
    
    MEMNODE_createLite(node+i);
  }
  
  for (u32 i = 0; i < vector->tail_; i++){
    (node+i)->ops_->setData((node+i),(vector->storage_+i)->data_,(vector->storage_+i)->size_);
  }

  for (u32 i = 0; i < vector_src->tail_; i++){
    (node+i+vector->tail_)->ops_->memCopy((node+i + vector->tail_),(vector_src->storage_+i)->data_,(vector_src->storage_+i)->size_);
  }

  MM->free(vector->storage_);
  vector->storage_ = node;
  vector->capacity_ = vector->capacity_ + vector_src->capacity_;
  vector->tail_ = vector->tail_ + vector_src->tail_;

  return kErrorCode_Ok;
}

s16 VECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *)){//cheked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == callback){
    kErrorCode_CallBackNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }

  for (u32 i = 0; i < vector->capacity_; i++){
    callback((vector->storage_+i));
  }

  return kErrorCode_Ok;
}

void VECTOR_print(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  printf("[VECTOR INFO] Address: %p\n",vector);
  printf("[VECTOR INFO] Head: %d\n",vector->head_);
  printf("[VECTOR INFO] Tail: %d\n",vector->tail_);
  printf("[VECTOR INFO] Lenght: %d\n",vector->tail_);
  printf("[VECTOR INFO] Capacity: %d\n",vector->capacity_);
  printf("[VECTOR INFO] Address: %p\n",vector->storage_);
  for(u32 i = 0; i < vector->tail_; i++){
    printf("\t[VECTOR INFO] Storage #%d:\n",i);
    (vector->storage_+i)->ops_->print((vector->storage_+i));
  }
  
}

