#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

struct vector_ops_s vector_ops = {0};

Vector* VECTOR_create(u16 capacity) {
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

s16 VECTOR_destroy(Vector *vector){
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

s16 VECTOR_softReset(Vector *vector){
  if( NULL != vector){
    if( NULL != vector->storage_){  
      for (u32 i = 0; i < vector->capacity_; i++){
        (vector->storage_+i)->ops_->softReset((vector->storage_+i));
      }

      return kErrorCode_Ok;    
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}

s16 VECTOR_reset(Vector *vector){
  if( NULL != vector){
    if( NULL != vector->storage_){
      for (u32 i = 0; i < vector->capacity_; i++){
        (vector->storage_+i)->ops_->reset((vector->storage_+i));
      }

      return kErrorCode_Ok;
    }

    return kErrorCode_StorageNULL;
  }

  return kErrorCode_VectorNULL;
}

s16 VECTOR_resize(Vector *vector, u16 new_size){
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
  
  if(new_size > vector->capacity_){
    // Al alza
    for (u32 i = 0; i < vector->capacity_; i++){

      MEMNODE_createLite(node_tmp+i);
      if(i<vector->tail_){
        (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));
      }
    }

    MM->free(vector->storage_);
  }else{
    // A la baja
    for (u32 i = 0; i < vector->capacity_; i++){

      if(i<new_size){
        MEMNODE_createLite(node_tmp+i);
        (node_tmp+i)->ops_->setData((node_tmp+i),((vector->storage_+i)->data_),((vector->storage_+i)->size_));

      }else{
        (vector->storage_+i)->ops_->reset(vector->storage_);
      }
    }


    MM->free(vector->storage_);
    vector->storage_ = node_tmp;
    vector->capacity_ = new_size;
    
    if(vector->tail_ > new_size){
      vector->tail_ = new_size;
    }


  }

  // new size == capacity
  return kErrorCode_Ok;
  
}

u16 VECTOR_capacity(Vector *vector){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }

  return vector->capacity_;
}

u16 VECTOR_lenght(Vector *vector){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if(vector->tail_ > vector->capacity_){
    return kErrorCode_VectorTailExceedsCapacity;
  }
  
  return vector->tail_;

}

bool VECTOR_isEmpty(Vector *vector){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }

  if(vector->tail_ == 0){
    return true;
  }

  return false;
}

bool VECTOR_isFull(Vector *vector){
  if( NULL == vector){
    return kErrorCode_VectorNULL;
  }

  // En el caso de que cuando se añada el ultimo elemento, el tail sea +1 respecto a la capacidad
  if(vector->tail_-1 == vector->capacity_){
    return true;
  }

  return false;
}


void* VECTOR_first(Vector *vector){

  if(NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }
  if( NULL != vector->storage_->data_){
    return vector->storage_->data_
  }
  return kErrorCode_DataNULL;

} 
void* VECTOR_last(Vector *vector){

  if(NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }

  int offset = 0;
  if(vector->tail_ > 0){

    offset = vector->tail_ -1;
  }


  if( NULL == (vector->storage_ + offset)->data_){
      
      return kErrorCode_DataNULL;
    }

  return (vector->storage_ + offset)->data_;
} 
void* VECTOR_at(Vector *vector, u16 position){

  if(NULL == vector){
    return kErrorCode_VectorNULL;
  }
  if( NULL == vector->storage_){
    return kErrorCode_StorageNULL;
  }
  if(position > vector->capacity_){
    return kErrorCode_VectorPositionExceedsCapacity;
  }
  if(position > vector->tail_){
    return kErrorCode_VectorPositionExceedsTail;
  }


  if( NULL == (vector->storage_ + position)->data_){
      
      return kErrorCode_DataNULL;
    }

  return (vector->storage_ + position)->data_;
} 


