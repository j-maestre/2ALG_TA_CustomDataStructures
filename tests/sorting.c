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
Vector *v2 = NULL;
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
u16 partition(Vector *vec, int low, int high) {
  
  u16 *pivot = (u16*) vec->ops_->at(vec,high); 

  u16 i = (low - 1);

  for (u16 j = low; j < high; j++) {

    if (*((u16*) vec->ops_->at(vec,j)) <= *pivot) {
      swap(vec,++i,j);
    }
  }

  swap(vec,i+1,high);
  
  // return the partition point
  return (i + 1);
}
 
void quickSort(Vector *vec, int low, int high) {
  if (low < high) {
    
    int pi = partition(vec, low, high);
    
    // recursive call on the left of pivot
    quickSort(vec, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(vec, pi + 1, high);
  }
}


//******* HeapSort ***********
void heapify(Vector *vec, u16 n, u16 i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && *((u16*) vec->ops_->at(vec,left)) > *((u16*) vec->ops_->at(vec,largest)))
        largest = left;


    if (right < n && *((u16*) vec->ops_->at(vec,right)) > *((u16*) vec->ops_->at(vec,largest)))
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(vec,i,largest);
        heapify(vec, n, largest);
    }
}

 // Main function to do heap sort
  void heapSort(Vector *vec, u16 n) {

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(vec, n, i);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {

      swap(vec,0,i);
      heapify(vec, i, 0);
    }
  }
 
//******* End HeapSort ***********

void InitDataForTest(){
  
    capacity = 1000;
    max_range = 150;
    v = NULL;
    v = VECTOR_create(capacity);

    v2 = NULL;
    v2 = VECTOR_create(capacity);

    for(u16 i = 0; i < capacity; i++){
        u16 *number = MM->malloc(sizeof(u16));
        u16 *number2 = MM->malloc(sizeof(u16));
        int r = rand()%max_range;
        *number = r;
        *number2 = r;
        v->ops_->insertFirst(v,number,sizeof(u16));
        v2->ops_->insertFirst(v2,number2,sizeof(u16));
    }
}

void printVector(Vector *vec){
    for (u16 i = 0; i < capacity; i++) {
        u16 *num = (u16*) vec->ops_->at(vec,i);
        printf("%d - ",*num);

    }
}

double elapsed_time = 0.0f;
void PrintTime(LARGE_INTEGER frequency, LARGE_INTEGER time_start, LARGE_INTEGER time_end){
	///////////////////////////////////////////////////////////////////////
	// compute the elapsed time in microseconds
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	printf("\n\nElapsed time: %f ms\n", elapsed_time);
	///////////////////////////////////////////////////////////////////////
	// compute the average time
	double average_time = elapsed_time / capacity;
	printf("Average time: %f ms\n", average_time);
	///////////////////////////////////////////////////////////////////////

}


int main()
{   
    LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval, 
    
    srand(time(NULL));
    InitDataForTest();
    QueryPerformanceFrequency(&frequency);
    

    printf("\n*** QuickSort Algorithm *** \n");
    printf("*** Un-ordered ***\n");
    printVector(v);

    printf("\n\n_____ Sorting... _____\n\n");

    QueryPerformanceCounter(&time_start);
    quickSort(v, 0, capacity - 1);
    QueryPerformanceCounter(&time_end);

    printf("*** Ordered ***\n");
    printVector(v);
   
    PrintTime(frequency,time_start,time_end);




    printf("\n\n\n*** HeapSort Algorithm *** \n");
    printf("*** Un-ordered ***\n");
    printVector(v2);

    printf("\n\n_____ Sorting... _____\n\n");

    QueryPerformanceCounter(&time_start);
    heapSort(v2, capacity);
    QueryPerformanceCounter(&time_end);

    printf("*** Ordered ***\n");
    printVector(v2);

    PrintTime(frequency,time_start,time_end);
 
    v->ops_->destroy(v);
    return 0;
}