#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EDK_MemoryManager/edk_memory_manager.h"
#include "EDK_MemoryManager/edk_platform_types.h"
#include "common_def.h"
#include "adt_vector.h"
#include "adt_list.h"
#include "adt_dllist.h"

Vector *v = NULL;
u16 capacity;
u16 data[5000];
u16 max_range;


void swap(Vector *vec, u16 firstPos, u16 secondPos){
  u16 *firstValue = (u16*) vec->ops_->at(vec,firstPos); 
  u16 *secondValue = (u16*) vec->ops_->at(vec,secondPos);

  u16 aux = *firstValue;
  *firstValue = *secondValue;
  *secondValue = aux; 

}

 
// function to find the partition position
u16 partition(Vector *v, int low, int high) {
  
  u16 *pivot = (u16*) v->ops_->at(v,high); 

  u16 i = (low - 1);

  for (u16 j = low; j < high; j++) {
    //if (array[j] <= *pivot) {
    if (*((u16*) v->ops_->at(v,j)) <= *pivot) {
      //i++;
      swap(v,++i,j);
    }
  }

  swap(v,i+1,high);
  
  // return the partition point
  return (i + 1);
}
 
void quickSort(Vector *v, int low, int high) {
  if (low < high) {
    
    int pi = partition(v, low, high);
    
    // recursive call on the left of pivot
    quickSort(v, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(v, pi + 1, high);
  }
}
 

void InitDataForTest(){
  
    capacity = 100;
    max_range = 150;
    v = NULL;
    v = VECTOR_create(capacity);

    for(u16 i = 0; i < capacity; i++){
        u16 *number = MM->malloc(sizeof(u16));
        int r = rand()%max_range;
        *number = r;
        v->ops_->insertFirst(v,number,sizeof(u16));
    }
}


int main()
{   
    srand(time(NULL));
    InitDataForTest();
    
    printf("\n*** QuickSort Algorithm *** \n");
    printf("*** Un-ordered ***\n");
    for (u16 i = 0; i < capacity; i++) {
        u16 *num = (u16*) v->ops_->at(v,i);
        printf("%d - ",*num);

    }
    printf("\n\n_____ Sorting... _____\n\n");
    quickSort(v, 0, capacity - 1);
 
    printf("*** Ordered ***\n");
    for (u16 i = 0; i < capacity; i++) {
        u16 *num = (u16*) v->ops_->at(v,i);
        printf("%d - ",*num);
    }
 
    return 0;
}