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



                                   

Vector* CVECTOR_create(u16 capacity) {

}

static void CVector_center(Vector *vector){

}

s16 CVECTOR_destroy(Vector *vector){

}

s16 CVECTOR_softReset(Vector *vector){
}

s16 CVECTOR_reset(Vector *vector){

}

s16 CVECTOR_resize(Vector *vector, u16 new_size){
  
}

u16 CVECTOR_capacity(Vector *vector){

}

u16 CVECTOR_lenght(Vector *vector){

}

boolean CVECTOR_isEmpty(Vector *vector){

}

boolean CVECTOR_isFull(Vector *vector){
  
}

void* CVECTOR_first(Vector *vector){

}

void* CVECTOR_last(Vector *vector){

} 

void* CVECTOR_at(Vector *vector, u16 position){

}

s16 CVECTOR_insertFirst(Vector *vector, void *data, u16 bytes){
  
} 

s16 CVECTOR_insertLast(Vector *vector, void *data, u16 bytes){

}

s16 CVECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position){

}

void* CVECTOR_extractFirst(Vector *vector){

}

void* CVECTOR_extractAt(Vector *vector, u16 position){

}

void* CVECTOR_extractLast(Vector *vector){

}

s16 CVECTOR_concat(Vector *vector, Vector *vector_src){

}

s16 CVECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *)){

}

void MVECTOR_print(Vector *vector){

  
}

