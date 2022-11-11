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
	rslt->head_ = 0;
	rslt->tail_ = 0;
	rslt->capacity_ = capacity;
	rslt->ops_ = &vector_ops;
	return rslt;
}