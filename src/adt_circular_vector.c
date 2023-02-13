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
#ifdef VERBOSE_
  printf("\x1B[34m[VERBOSE_]\x1B[37m");
  printf("CVector has been created in address 0x%p[0x%p-0x%p] Capacity:%d \n", vector, vector->storage_, (vector->storage_ + vector->capacity_), vector->capacity_);
#endif
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

  if(vector->tail_ >= vector->head_){
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
    vector->head_ = vector->capacity_-1;
    (vector->storage_)->ops_->setData(vector->storage_ + (vector->head_),data, bytes);

  }else{

    vector->head_ = ((int)vector->head_ - 1) % vector->capacity_;
    (vector->storage_)->ops_->setData(vector->storage_ + (vector->head_),data, bytes);
  }
  
#ifdef VERBOSE_
    printf("\x1B[34m[VERBOSE_]\x1B[37m");
    printf("Moveing memory 0x%p[0x%p]\n", vector->storage_ + (vector->head_), data);
#endif

 
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
  vector->tail_ = (vector->tail_+1) % vector->capacity_ ;

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
    vector->storage_->ops_->setData(vector->storage_ + vector->tail_, data, bytes);
    vector->tail_ = (vector->tail_+1) % vector->capacity_;
    return kErrorCode_Ok;
  }

  // Se ha pasado del tail, lo metemos al final y au
  if(position > vector->tail_){
    vector->storage_->ops_->setData(vector->storage_ + vector->tail_, data, bytes);
    vector->tail_ = (vector->tail_+1) % vector->capacity_;
    return kErrorCode_Ok;
  }

  MemoryNode *current_src = vector->storage_;
  MemoryNode *current_dst = vector->storage_;
  MemoryNode *end = (vector->storage_ + position);
  
  // Al final
  // TODO distinguir si esta mas cerca del principio o del final
  u16 index_dst = vector->tail_;
  u16 index_src = vector->tail_ - 1;

  if(vector->tail_ == 0){
    index_src = vector->capacity_ - 1;
  }

  while(index_dst != position){
    (current_dst+index_dst)->ops_->setData((current_dst+index_dst), (current_src + index_src)->data_, (current_src + index_src)->size_);

    if(index_dst == 0){
      index_dst = vector->capacity_;
    }
    if(index_src == 0){
      index_src = vector->capacity_;
    }

    index_dst--;
    index_src--;

  };


  (current_dst + index_dst)->ops_->setData((current_dst + index_dst),data,bytes);
  return kErrorCode_Ok;
}

void* CVECTOR_extractFirst(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  if(CVECTOR_isEmpty(vector)){
    return NULL;
  }

  void *data_tmp = (vector->storage_ + vector->head_)->data_;
  vector->storage_->ops_->softReset(vector->storage_ + vector->head_);
  vector->head_ = (vector->head_+1) % vector->capacity_;

  return data_tmp;
}

void* CVECTOR_extractAt(Vector *vector, u16 position){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == vector->storage_){
    return NULL;
  }

  if(CVECTOR_isEmpty(vector)){
    return NULL;
  }

  //if(position > (vector->head_ + vector->tail_)){
  if(position > (vector->tail_ - vector->head_) || position < 0){ // si la posicion esta fuera del rango
    return NULL;
  }

  //Reservamos el data seleccionado
  void *data_tmp = (vector->storage_ + (vector->head_ + position))->data_;

  if((vector->tail_ - vector->head_) > 1){
    //Tiene mas de uno, los movemos todos uno a la izquierda empezando por la position
    for (u32 i = position + vector->head_; i != vector->tail_; i = (i + 1) % vector->capacity_){
      ((vector->storage_)+i)->ops_->setData(((vector->storage_)+i),((vector->storage_)+i+1)->data_,((vector->storage_)+i+1)->size_);
    }

    //El ultimo elemento lo eliminamos porque esta duplicado
    (vector->storage_+(vector->tail_-1))->ops_->softReset(vector->storage_+(vector->tail_-1));
  }

  vector->tail_ = (vector->tail_ - 1) % vector->capacity_ ;
  return data_tmp;
}

void* CVECTOR_extractLast(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == (vector->storage_)+ (vector->tail_ - 1)){
    return NULL;
  }

  if(CVECTOR_isEmpty(vector)){
    return NULL;
  }

  void *data = (vector->storage_ + (vector->tail_ - 1))->data_;
  vector->tail_ -= (vector->tail_-1) % vector->capacity_;
  vector->storage_->ops_->softReset(vector->storage_+vector->tail_);

  return data;
}

s16 CVECTOR_concat(Vector *vector, Vector *vector_src){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector_src){
    return kErrorCode_VectorNULL;
  }

  if( NULL == vector->storage_ || NULL == vector_src->storage_){
    return kErrorCode_StorageNULL;
  }

  

  u16 real_new_size = (vector->capacity_ + vector_src->capacity_);
  s16 length = CVECTOR_lenght(vector) + CVECTOR_lenght(vector_src);

  // Reservamos nuevo vector con el tamano de los dos
  MemoryNode *node = MM->malloc(sizeof(MemoryNode) * real_new_size);
  if (NULL == node) {
    return kErrorCode_NoMemory;
  }

  
  // Create lite de todos los memory node
  for (u32 i = 0; i < real_new_size; i++){
    MEMNODE_createLite(node+i);
  }
  

  //Primero sacar cuanto tenemos que meter sumando los dos vectores
  //Luego sacar la primera posicion donde tenemos que empezar a meter

  s16 new_head = ((real_new_size - length) / 2);
  s16 new_tail = (new_head + length); // + 1 ???

  MemoryNode *current_dst = node + new_head;
  MemoryNode *current_src = vector->storage_ + vector->head_;
  MemoryNode *end = vector->storage_ + vector->tail_;

  if(!CVECTOR_isEmpty(vector)){
    do {
#ifdef VERBOSE_
      printf("\x1B[34m[VERBOSE_]\x1B[37m");
      printf("Moveing memory from 0x%p[0x%p] to 0x%p[0x%p]\n", current_src, current_src->data_, current_dst, current_dst->data_);
#endif
      current_dst->ops_->setData(current_dst, current_src->data_, current_src->size_);
      current_src->ops_->softReset(current_src);
      current_dst++;
      current_src++;
    } while (current_src != end);
  }

  current_src = vector_src->storage_ + vector_src->head_;
  end = vector_src->storage_ + vector_src->tail_;

  if(!CVECTOR_isEmpty(vector_src)){
    do{
#ifdef VERBOSE_
      printf("\x1B[34m[VERBOSE_]\x1B[37m");
      printf("Copying memory from 0x%p[0x%p] to 0x%p[0x%p]\n", current_src, current_src->data_, current_dst, current_dst->data_);
#endif
      current_dst->ops_->memCopy(current_dst, current_src->data_, current_src->size_);
      current_dst++;
      current_src++;
    }while(current_src != end);

  }


  MM->free(vector->storage_);
  vector->storage_ = node;
  vector->capacity_ = real_new_size;
  vector->tail_ = new_tail;
  vector->head_ = new_head;

  MemoryNode* data;
  for (int i = 0; i < vector->capacity_; i++)
  {
    data = (vector->storage_ + i);
    for (int j = 0; j < vector->capacity_; j++)
    {
      if (data->data_ == (vector->storage_ + j)->data_ && i != j && (data->data_ != NULL || (vector->storage_ + j)->data_ != NULL))
      {
        printf("Same addres in diferents MemoryNodes\n\tMemoryNode1 -> %p\n\t\tdata_ -> %p\n\tMemoryNode2 -> %p\n\t\tdata_ -> %p\n", data, data->data_, (vector->storage_ + j), (vector->storage_ + j)->data_);
      }
    }
      
  }

  return kErrorCode_Ok;
}

s16 CVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *)){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == callback){
    return kErrorCode_CallBackNULL;
  }
  if( NULL == (vector->storage_ + vector->head_)){
    return kErrorCode_StorageNULL;
  }

  for (u32 i = vector->head_; i != vector->tail_; i = (i+1)%vector->capacity_){
    callback((vector->storage_+i));
  }

  return kErrorCode_Ok;
}

void CVECTOR_print(Vector *vector){
  if( NULL == vector){
    return NULL;
  }
  if( NULL == (vector->storage_ + vector->head_)){
    return NULL;
  }

  printf("[CVECTOR INFO] Address: %p\n",vector);
  printf("[CVECTOR INFO] Head: %d\n",vector->head_);
  printf("[CVECTOR INFO] Tail: %d\n",vector->tail_);
  printf("[CVECTOR INFO] Lenght: %d\n",CVECTOR_lenght(vector));
  printf("[CVECTOR INFO] Capacity: %d\n",vector->capacity_);
  printf("[CVECTOR INFO] Address: %p\n",vector->storage_);

  for(u32 i = vector->head_; i < vector->tail_; i++){
    printf("\t[CVECTOR INFO] Storage #%d:\n",i);
    (vector->storage_+i)->ops_->print((vector->storage_+i));
  }
  
}

