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
