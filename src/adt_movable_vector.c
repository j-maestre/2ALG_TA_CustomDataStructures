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
  for (MemoryNode *current = rslt->storage_, 
       *end = (rslt->storage_ + (rslt->capacity_ - 1)); current != end; current++) 
  {
    MEMNODE_createLite(current);
  }
	rslt->ops_ = &mvector_ops;
	return rslt;
}

static void MVector_center(Vector *vector){ // Checked by xema && hector

//Version 2.0, en vez de reservar, lo movemos x posiciones izquierda o derecha
  //Comprobamos que no este lleno
  if(vector->tail_ < vector->capacity_){
    u16 mitad = vector->capacity_ / 2.0f;
    u16 inicio = (vector->tail_-1) / 2.0;
    u16 new_head = mitad - inicio;
    u16 new_tail = new_head + (vector->tail_ - vector->head_);

    MemoryNode *aux;
    aux = (MemoryNode *) MM->malloc(sizeof(MemoryNode) * vector->capacity_);
    u16 indexOriginal = vector->head_;
    

    // Rellenamos el memnode auxiliar centrado con los valores del vector original
    for(u32 i = new_head; i < new_tail; i++){
      aux->ops_->setData((aux+i),(vector->storage_ + indexOriginal)->data_,(vector->storage_ + indexOriginal)->size_);
      indexOriginal++;
    }
    
    MM->free(vector->storage_);
    vector->storage_ = aux;
    vector->head_ = new_head;
    vector->tail_ = new_tail;

  }

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



s16 MVECTOR_resize(Vector *vector, u16 new_size){ //checked by hector && xema
  if( NULL == vector){

    return kErrorCode_VectorNULL; 
  }

  if(new_size == 0){
    return kErrorCode_SizeZERO;
  }

  u16 real_size = new_size << 1;

  if( real_size == vector->capacity_){
    return kErrorCode_Ok;
  }
  

  MemoryNode *new_storage = (MemoryNode *) MM->malloc(sizeof(MemoryNode) * real_size);

  if (new_storage == NULL)
    return kErrorCode_NoMemory;


  MemoryNode *current_src = new_storage;
  MemoryNode *end = new_storage + real_size;

  do {
    MEMNODE_createLite(current_src);
    current_src++;
  } while(current_src != end);

  u16 new_head = ((real_size - (vector->tail_ - vector->head_)) / 2);
  u16 new_tail = (new_head + (vector->tail_ - vector->head_));

  MemoryNode *current_dst;

  if (real_size > vector->capacity_) {
    // Al alza

    current_dst = new_storage + new_head;
    end = current_dst + (new_tail - 1);
    current_src = vector->storage_ + vector->head_;

    do {
      current_dst->ops_->setData(current_dst, current_src->data_, current_src->size_);
      current_dst++;
      current_src++;
    } while (current_dst != end);

  } else {
    // A la baja

    current_dst = new_storage + new_head;
    current_src = vector->storage_ + vector->head_;
    end = current_src + (vector->tail_ - 1);
    MemoryNode *max_dst = current_dst + (new_size - 1);

    do {

      if (current_dst <= max_dst) {
        current_dst->ops_->setData(current_dst, current_src->data_, current_src->size_);
      } else {
        current_src->ops_->reset(current_src);
      }
      
      current_dst++;
      current_src++;
    } while (current_src != end);

    if (new_tail > new_size) {
      new_tail = new_size;
    }
    
  }

  MM->free(vector->storage_);
  vector->storage_ = new_storage;
  vector->capacity_ = new_size;
  vector->tail_ = new_tail;

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
 
  /*if(vector->tail_ > vector->capacity_){
    return 0;
  }*/
  
  return vector->tail_ - vector->head_;

}

boolean MVECTOR_isEmpty(Vector *vector){//TODO revise
  if( NULL == vector){
    return False;
  }

  if((vector->tail_ - vector->head_) == 0){
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

s16 MVECTOR_insertFirst(Vector *vector, void *data, u16 bytes){//checked by xema && hector
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

  //Comprobamos que head no esta al principio
  if(vector->head_ == 0){
    //Si hay espacio, aprovechamos y lo centramos
    MVector_center(vector);
  }

  //Metemos en head-1 el nuevo data
  (vector->storage_)->ops_->setData((vector->storage_ + (vector->head_-1) ),data,bytes);

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
