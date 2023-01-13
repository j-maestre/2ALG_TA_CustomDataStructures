#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_movable_vector.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 MVECTOR_destroy(Vector *vector);
static s16 MVECTOR_softReset(Vector *vector);
static s16 MVECTOR_reset(Vector *vector);
static s16 MVECTOR_resize(Vector *vector, u16 new_size);
static u16 MVECTOR_capacity(Vector *vector);
static u16 MVECTOR_lenght(Vector *vector);
static boolean MVECTOR_isEmpty(Vector *vector);
static boolean MVECTOR_isFull(Vector *vector);
static void* MVECTOR_first(Vector *vector);
static void* MVECTOR_last(Vector *vector);
static void* MVECTOR_at(Vector *vector, u16 position);
static s16 MVECTOR_insertFirst(Vector *vector, void *data, u16 bytes);
static s16 MVECTOR_insertLast(Vector *vector, void *data, u16 bytes);
static s16 MVECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position);
static void* MVECTOR_extractFirst(Vector *vector);
static void* MVECTOR_extractLast(Vector *vector);
static void* MVECTOR_extractAt(Vector *vector, u16 position);
static s16 MVECTOR_concat(Vector *vector, Vector *vector_src);
static s16 MVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *));
static void MVECTOR_print(Vector *vector);

struct vector_ops_s mvector_ops = { .destroy = MVECTOR_destroy,
                                   .softReset = MVECTOR_softReset,
                                   .reset = MVECTOR_reset,
                                   .resize = MVECTOR_resize,
                                   .capacity = MVECTOR_capacity,
                                   .length = MVECTOR_lenght,
                                   .isEmpty = MVECTOR_isEmpty,
                                   .isFull = MVECTOR_isFull,
                                   .first = MVECTOR_first,
                                   .last = MVECTOR_last,
                                   .at = MVECTOR_at,
                                   .insertFirst = MVECTOR_insertFirst,
                                   .insertLast = MVECTOR_insertLast,
                                   .insertAt = MVECTOR_insertAt,
                                   .extractFirst = MVECTOR_extractFirst,
                                   .extractLast = MVECTOR_extractLast,
                                   .extractAt = MVECTOR_extractAt,
                                   .concat = MVECTOR_concat,
                                   .traverse = MVECTOR_traverse,
                                   .print = MVECTOR_print                   
                                   };



                                   

Vector* MVECTOR_create(u16 capacity) { //* checked by xema & hector
	if (0 >= capacity) {
		return NULL;
	}
	Vector* rslt = (Vector *)MM->malloc(sizeof(Vector));
	if (NULL == rslt) {
		return NULL;
	}
  rslt->capacity_ = capacity << 1;
  rslt->head_ = capacity;
  rslt->tail_ = capacity;
	rslt->storage_ = (MemoryNode *) MM->malloc(sizeof(MemoryNode) * rslt->capacity_);
	if (NULL == rslt->storage_) {
		MM->free(rslt);
		return NULL;
	}
	for (u32 i = 0; i < rslt->capacity_; i++) {
		MEMNODE_createLite((rslt->storage_ + i));
	}
	rslt->ops_ = &mvector_ops;
	return rslt;
}

s16 MVECTOR_destroy(Vector *vector){//* checked by xema & hector
  if( NULL != vector){
    if(NULL != vector->storage_){

      for (u32 i = vector->head_; i < vector->tail_; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+i));
      }
      MM->free(vector->storage_);

    }

    MM->free(vector);
  }

  return kErrorCode_Ok;
}


s16 MVECTOR_softReset(Vector *vector){ //* checked by xema & hector
  if( NULL != vector){
    if( NULL != vector->storage_){  
      for (u32 i = vector->head_; i < vector->tail_; i++){
        (vector->storage_+i)->ops_->softReset((vector->storage_+i));
      }
      vector->tail_ = vector->capacity_ >> 1;
      return kErrorCode_Ok;    
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}


s16 MVECTOR_reset(Vector *vector){//* checked by xema & hector
  if( NULL != vector){
    if( NULL != vector->storage_){
      for (u32 i = vector->head_; i < vector->tail_; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+i));
      }
      vector->tail_ = vector->capacity_ >> 1;
      return kErrorCode_Ok;
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}



s16 MVECTOR_resize(Vector *vector, u16 new_size){ //TODO revise
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
  for (u32 i = vector->head_; i < new_size; i++) {
    MEMNODE_createLite(node_tmp + i);
  }
  
  if(new_size > vector->capacity_){
    // Al alza
    for (u32 i = vector->head_; i < vector->tail_; i++){

      (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));
    }

  }else{
    // A la baja
    for (u32 i = vector->head_; i < vector->tail_; i++){

      if(i<new_size){
        (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));

      }else{
        (vector->storage_+i)->ops_->reset(vector->storage_ + i);
      }
    }




  }

  MM->free(vector->storage_);
  vector->storage_ = node_tmp;
  vector->capacity_ = new_size << 1;
    
  if(vector->tail_ > vector->capacity_){
    vector->tail_ = vector->capacity_;
  }

  // new size == capacity
  return kErrorCode_Ok;
  
}






u16 MVECTOR_capacity(Vector *vector){//TODO revise
  if( NULL == vector){
    return 0;
  }

  return vector->capacity_ >> 1;
}

u16 MVECTOR_lenght(Vector *vector){//TODO revise
  if( NULL == vector){
    return 0;
  }
  if(vector->tail_ > vector->capacity_){
    return 0;
  }
  
  return vector->tail_ >> 1;

}

boolean MVECTOR_isEmpty(Vector *vector){//TODO revise
  if( NULL == vector){
    return False;
  }

  if(vector->tail_ == 0){
    return True;
  }

  return False;
}

boolean MVECTOR_isFull(Vector *vector){//TODO revise
  if( NULL == vector){
    return False;
  }
  // En el caso de que cuando se añada el ultimo elemento, el tail sea +1 respecto a la capacidad
  return ((vector->tail_ - vector->head_) == (vector->capacity_ >> 1));
}

void* MVECTOR_first(Vector *vector){//? revise

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  return (vector->storage_ + vector->head_)->data_;

}

void* MVECTOR_last(Vector *vector){//TODO revise

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  u32 offset = 0;
  if(vector->tail_ > 0){
    offset = vector->tail_ -1;
  } else {
    return NULL;
  }
  return (vector->storage_ + offset)->data_;
} 

void* MVECTOR_at(Vector *vector, u16 position){//TODO revise

  if(NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  if(position >= vector->tail_ >> 1){
    return NULL;
  }
  return (vector->storage_ + vector->head_ + position)->data_;
}

s16 MVECTOR_insertFirst(Vector *vector, void *data, u16 bytes){//
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if (NULL == vector->storage_) {
    return kErrorCode_StorageNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  // Mover todo lo que haya una posicion a la izquierda en caso de que haya algo y no se pase
  if(MVECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  if(!MVECTOR_isEmpty(vector)){


    //Insert first and move head
    // comprobar que head no sea 0, en caso de que sea 0 pos hacemos lo de siempre
    if(vector->head_ == 0 && vector->tail_ < vector->capacity_){
      //No hay hueco a la izquirda pero el vector aun no esta lleno

      // Movemos las cosas
      for (u32 i = vector->tail_; i > 0 ; i--){
        (((vector->storage_)+i)->ops_)->setData( ((vector->storage_)+i) , ((vector->storage_)+(i-1) )->data_, ((vector->storage_)+(i-1))->size_);
      }
      (vector->storage_)->ops_->setData(vector->storage_,data, bytes);
    
    }else{
      // Hay hueco a la izquierda
      vector->head_--;
      (vector->storage_ + (vector->head_))->ops_->setData(vector->storage_,data, bytes);
    }
    
  }



  vector->tail_++;

  return kErrorCode_Ok;
} 

s16 MVECTOR_insertLast(Vector *vector, void *data, u16 bytes){//cheked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if (NULL == vector->storage_) {
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if(!MVECTOR_isFull(vector)){
    
    ((vector->storage_) + (vector->tail_))->ops_->setData((vector->storage_) + (vector->tail_),data,bytes);
    vector->tail_++;
    return kErrorCode_Ok;
  }

  return kErrorCode_VectorFull;
}

s16 MVECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position){//cheked
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if (NULL == vector->storage_) {
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if(bytes == 0){
    return kErrorCode_ZeroBytes;
  }

  if( position > vector->tail_){
    position = vector->tail_;
  }

  if(MVECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  if(!MVECTOR_isEmpty(vector)){
    // El vector tiene cosas, hay que moverlas
    for (u32 i = vector->tail_; i > position ; i--){
      (((vector->storage_)+i)->ops_)->setData( ((vector->storage_)+i) , ((vector->storage_)+(i-1) )->data_, ((vector->storage_)+(i-1))->size_);
    }
    
  }
  
  ((vector->storage_)+position)->ops_->setData(((vector->storage_)+position),data,bytes);
  vector->tail_++;

  return kErrorCode_Ok;
}

void* MVECTOR_extractFirst(Vector *vector){//
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  if(MVECTOR_isEmpty(vector)){
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

void* MVECTOR_extractAt(Vector *vector, u16 position){//
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

void* MVECTOR_extractLast(Vector *vector){//
  if( NULL == vector){
    return NULL;
  }
  if( NULL == (vector->storage_)+(vector->tail_)){
    return NULL;
  }

  if(MVECTOR_isEmpty(vector)){
    return NULL;
  }

  void *data_tmp = ((vector->storage_)+(vector->tail_ - 1))->data_;
  vector->storage_->ops_->softReset((vector->storage_) + (vector->tail_ - 1));
  vector->tail_--;

  return data_tmp;
}

s16 MVECTOR_concat(Vector *vector, Vector *vector_src){//
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
  if (NULL == node) {
    return kErrorCode_NoMemory;
  }
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

s16 MVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *)){//cheked
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

void MVECTOR_print(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  printf("[MVECTOR INFO] Address: %p\n",vector);
  printf("[MVECTOR INFO] Head: %d\n",vector->head_);
  printf("[MVECTOR INFO] Tail: %d\n",vector->tail_);
  printf("[MVECTOR INFO] Lenght: %d\n",vector->tail_);
  printf("[MVECTOR INFO] Capacity: %d\n",vector->capacity_);
  printf("[MVECTOR INFO] Address: %p\n",vector->storage_);
  for(u32 i = 0; i < vector->tail_; i++){
    printf("\t[MVECTOR INFO] Storage #%d:\n",i);
    (vector->storage_+i)->ops_->print((vector->storage_+i));
  }
  
}

