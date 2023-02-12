#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_movable_vector.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 CVECTOR_destroy(Vector *vector);
static s16 CVECTOR_softReset(Vector *vector);
static s16 CVECTOR_reset(Vector *vector);
static s16 CVECTOR_resize(Vector *vector, u16 new_size);
static u16 CVECTOR_capacity(Vector *vector);
static u16 CVECTOR_lenght(Vector *vector);
static boolean CVECTOR_isEmpty(Vector *vector);
static boolean CVECTOR_isFull(Vector *vector);
static void* CVECTOR_first(Vector *vector);
static void* CVECTOR_last(Vector *vector);
static void* CVECTOR_at(Vector *vector, u16 position);
static s16 CVECTOR_insertFirst(Vector *vector, void *data, u16 bytes);
static s16 CVECTOR_insertLast(Vector *vector, void *data, u16 bytes);
static s16 CVECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position);
static void* CVECTOR_extractFirst(Vector *vector);
static void* CVECTOR_extractLast(Vector *vector);
static void* CVECTOR_extractAt(Vector *vector, u16 position);
static s16 CVECTOR_concat(Vector *vector, Vector *vector_src);
static s16 CVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *));
static void CVECTOR_print(Vector *vector);

struct vector_ops_s mvector_ops = { .destroy = CVECTOR_destroy,
                                   .softReset = CVECTOR_softReset,
                                   .reset = CVECTOR_reset,
                                   .resize = CVECTOR_resize,
                                   .capacity = CVECTOR_capacity,
                                   .length = CVECTOR_lenght,
                                   .isEmpty = CVECTOR_isEmpty,
                                   .isFull = CVECTOR_isFull,
                                   .first = CVECTOR_first,
                                   .last = CVECTOR_last,
                                   .at = CVECTOR_at,
                                   .insertFirst = CVECTOR_insertFirst,
                                   .insertLast = CVECTOR_insertLast,
                                   .insertAt = CVECTOR_insertAt,
                                   .extractFirst = CVECTOR_extractFirst,
                                   .extractLast = CVECTOR_extractLast,
                                   .extractAt = CVECTOR_extractAt,
                                   .concat = CVECTOR_concat,
                                   .traverse = CVECTOR_traverse,
                                   .print = CVECTOR_print                   
                                   };



                                   

Vector* CVECTOR_create(u16 capacity) { // Checked by xema && Hector
    if (0 >= capacity) {
		return NULL;
    }
    Vector* vector = (Vector *)MM->malloc(sizeof(Vector));
    if (NULL == vector) {
    	return NULL;
    }
    vector->capacity_ = capacity;
    vector->tail_ = 0;
    vector->head_ = 0;
	vector->storage_ = (MemoryNode *) MM->malloc(sizeof(MemoryNode) * capacity);

	if (NULL == vector->storage_) {
		MM->free(vector);
		return NULL;
	}
    
    for (MemoryNode *current = vector->storage_, 
        *end = (vector->storage_ + vector->capacity_); current != end; current++) 
    {
        MEMNODE_createLite(current);
    }
	vector->ops_ = &mvector_ops;
	return vector;
}

s16 CVECTOR_destroy(Vector *vector){ // TODO revise
  if ( NULL != vector){
    if( NULL != vector->storage_){
      u16 lenght = CVECTOR_lenght(vector);
        for(u32 i = vector->head_; i < lenght; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+((vector->head_+i)%vector->capacity_)));
      }

      MM->free(vector->storage_);
    }

    MM->free(vector);
  }
  return kErrorCode_Ok;
}

s16 CVECTOR_softReset(Vector *vector){ // TODO revise
  if ( NULL != vector){
    if( NULL != vector->storage_){
      u16 lenght = CVECTOR_lenght(vector);
      for(u32 i = vector->head_; i < lenght; i++){
        (vector->storage_+i)->ops_->softReset((vector->storage_+((vector->head_+i)%vector->capacity_)));
      }
      vector->head_ = 0;
      vector->tail_ = 0;
      return kErrorCode_Ok;
    }
    
    return kErrorCode_StorageNULL;
  }
  return kErrorCode_VectorNULL;
}

s16 CVECTOR_reset(Vector *vector){ // TODO revise
  if ( NULL != vector){
    if( NULL != vector->storage_){
      u16 lenght = CVECTOR_lenght(vector);
      for(u32 i = 0; i < lenght; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+((vector->head_+i)%vector->capacity_)));
      }
      vector->head_ = 0;
      vector->tail_ = 0;
      return kErrorCode_Ok;
    }
    
    return kErrorCode_StorageNULL;
  }
  return kErrorCode_VectorNULL;

}

s16 CVECTOR_resize(Vector *vector, u16 new_size){

 return kErrorCode_Ok; 
}

u16 CVECTOR_capacity(Vector *vector){
  if( NULL == vector){
    return 0;
  }

  return vector->capacity_;
}

u16 CVECTOR_lenght(Vector *vector){
  if( NULL == vector){
      return kErrorCode_VectorNULL;
  }

  if(vector->tail_ > vector->head_){
      return vector->tail_ - vector->head_;
  }else{
      return (vector->capacity_ - vector->head_) + vector->tail_ - 1;
  }

}

boolean CVECTOR_isEmpty(Vector *vector){
  if( NULL == vector){
    return False;
  }

  return vector->ops_->length(vector) == 0;
}

boolean CVECTOR_isFull(Vector *vector){
  if (vector == NULL)
    return False;

  return (vector->ops_->length(vector) == vector->capacity_);
}

void* CVECTOR_first(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  return (vector->storage_ + vector->head_)->data_;
}

void* CVECTOR_last(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }
  return (vector->storage_ + (vector->tail_ - 1))->data_;

} 

void* CVECTOR_at(Vector *vector, u16 position){
   if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  return (vector->storage_ + (vector->head_ + (position%vector->capacity_))); // me huele a chamusquina
}

s16 CVECTOR_insertFirst(Vector *vector, void *data, u16 bytes){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(CVECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  if(vector->head_ == 0){
    (vector->storage_)->ops_->setData(vector->storage_ + (vector->capacity_ - 1),data, bytes);
  }else{
    (vector->storage_)->ops_->setData(vector->storage_ + (vector->head_- 1),data, bytes);
  }

  vector->head_--;
  return kErrorCode_Ok;
  
} 

s16 CVECTOR_insertLast(Vector *vector, void *data, u16 bytes){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(CVECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  (vector->storage_)->ops_->setData(vector->storage_ + (vector->tail_),data, bytes);
  vector->tail_++;

  return kErrorCode_Ok;
}

s16 CVECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }
  if( NULL == data){
    return kErrorCode_DataNULL;
  }
  if( bytes <= 0){
    return kErrorCode_ZeroBytes;
  }
  if(CVECTOR_isFull(vector)){
    return kErrorCode_VectorFull;
  }

  // Esta vacio, lo metemos al principio y au
  if(CVECTOR_isEmpty(vector)){
    vector->storage_->ops_->setData(vector->storage_ + vector->head_, data, bytes);
    vector->tail_++;
    return kErrorCode_Ok;
  }

  // Se ha pasado del tail, lo metemos al final y au
  if(position > vector->tail_){
    vector->storage_->ops_->setData(vector->storage_ + vector->tail_, data, bytes);
    vector->tail_++;
    return kErrorCode_Ok;
  }

  MemoryNode *current_src;
  MemoryNode *current_dst;
  MemoryNode *end = (vector->storage_ + position);

  // Mover las cosas antes de meterlas
  if(position - (vector->tail_ - 1) < position - vector->head_){
    //Esta mas cerca del final
    current_dst = (vector->storage_ + (vector->tail_));
    current_src = (vector->storage_ + (vector->tail_ - 1));
    u16 index = 0;
    
    do{
      current_dst->ops_->setData(current_dst,current_src->data_,current_src->size_);
      current_dst -= index++%vector->capacity_;
      current_src -= index++%vector->capacity_;
    }while(current_dst != end);
    
    
    vector->tail_++;
  }else{
    //Esta mas cerca del principio
    current_dst = (vector->storage_ + (vector->head_ - 1));
    current_src = (vector->storage_ + (vector->head_));
    u16 index = 0;
    do{
      current_dst->ops_->setData(current_dst,current_src->data_,current_src->size_);
      current_dst += index++%vector->capacity_;
      current_src += index++%vector->capacity_;
    }while(current_dst != end);
    
    vector->head_ -= (vector->head_ - 1) % vector->capacity_;

  }

  current_dst->ops_->setData(current_dst,data,bytes);
  return kErrorCode_Ok;
}

void* CVECTOR_extractFirst(Vector *vector){

  return NULL;
}

void* CVECTOR_extractAt(Vector *vector, u16 position){
  return NULL;
}

void* CVECTOR_extractLast(Vector *vector){
  return NULL;
}

s16 CVECTOR_concat(Vector *vector, Vector *vector_src){


  return kErrorCode_Ok;
}

s16 CVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *)){
  return kErrorCode_Ok;
}

void CVECTOR_print(Vector *vector){

  
}

