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
Vector *v3 = NULL;
Vector *v4 = NULL;
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

//******* Bubble Sort ************
void bubbleSort(Vector *v, u16 size) {

  // loop to access each array element
  for (u16 step = 0; step < size - 1; ++step) {
      
    // loop to compare array elements
    for (u16 i = 0; i < size - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      //if (array[i] > array[i + 1]) {
      if (*((u16*) v->ops_->at(v,i)) > *((u16*) v->ops_->at(v,i+1))) {
        
        // swapping occurs if elements
        // are not in the intended order
        swap(v,i,i+1);
        //int temp = array[i];
        //array[i] = array[i + 1];
        //array[i + 1] = temp;
      }
    }
  }
}
//******* End Bubble Sort ************


//******* Cocktail sort ************
void CocktailSort(Vector *v, u16 n){
    u8 swapped = 1;
    int start = 0;
    int end = n - 1;
 
    while (swapped == 1) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = 0;
 
        // loop from left to right same as
        // the bubble sort
        //for (u16 i = start; i < end; ++i) {
        for (s16 i = 0; i < end; ++i) {
            //if (a[i] > a[i + 1]) {
            if (*((u16*) v->ops_->at(v,i)) > *((u16*) v->ops_->at(v,i+1))) {
                //swap(a[i], a[i + 1]);
                swap(v,i,i+1);
                swapped = 1;
            }
        }
 
        // if nothing moved, then array is sorted.
        if (swapped == 0)
            break;
 
        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = 0;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        for (s16 i = end - 1; i >= start; --i) {
            //if (a[i] > a[i + 1]) {
            if (*((u16*) v->ops_->at(v,i)) >= *((u16*) v->ops_->at(v,i+1))) {
                //swap(a[i], a[i + 1]);
                swap(v, i, i+1);
                swapped = 1;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}


//******* End Cocktail sort ************


void InitDataForTest(){
  
    capacity = 10;
    max_range = 1500;
    v = NULL;
    v = VECTOR_create(capacity);

    v2 = NULL;
    v2 = VECTOR_create(capacity);
    v3 = VECTOR_create(capacity);
    v4 = VECTOR_create(capacity);

    for(u16 i = 0; i < capacity; i++){
        u16 *number = MM->malloc(sizeof(u16));
        u16 *number2 = MM->malloc(sizeof(u16));
        u16 *number3 = MM->malloc(sizeof(u16));
        u16 *number4 = MM->malloc(sizeof(u16));
        int r = rand()%max_range;
        *number = r;
        *number2 = r;
        *number3 = r;
        *number4 = r;
        v->ops_->insertFirst(v,number,sizeof(u16));
        v2->ops_->insertFirst(v2,number2,sizeof(u16));
        v3->ops_->insertFirst(v3,number3,sizeof(u16));
        v4->ops_->insertFirst(v4,number4,sizeof(u16));
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
    
    printf("Init sorting test with %d capacity and 0 - %d range\n\n",capacity,max_range);

    printf("\n*** QuickSort Algorithm *** \n");
    //printf("*** Un-ordered ***\n");
    //printVector(v);
    //printf("\n\n_____ Sorting... _____\n\n");

    QueryPerformanceCounter(&time_start);
    quickSort(v, 0, capacity - 1);
    QueryPerformanceCounter(&time_end);

    //printf("*** Ordered ***\n");
    //printVector(v);
   
    PrintTime(frequency,time_start,time_end);


    printf("\n*** HeapSort Algorithm *** \n");
    //printf("*** Un-ordered ***\n");
    //printVector(v2);
    //printf("\n\n_____ Sorting... _____\n\n");

    QueryPerformanceCounter(&time_start);
    heapSort(v2, capacity);
    QueryPerformanceCounter(&time_end);

    //printf("*** Ordered ***\n");
    //printVector(v2);
    PrintTime(frequency,time_start,time_end);
 
    printf("\n*** Bubble Sort Algorithm *** \n");
    //printf("*** Un-ordered ***\n");
    //printVector(v3);
    //printf("\n\n_____ Sorting... _____\n\n");

    QueryPerformanceCounter(&time_start);
    bubbleSort(v3, capacity);
    QueryPerformanceCounter(&time_end);
    //printf("*** Ordered ***\n");
    //printVector(v3);
    PrintTime(frequency,time_start,time_end);


    printf("\n*** Cocktail sort Algorithm *** \n");
    QueryPerformanceCounter(&time_start);
    CocktailSort(v4,capacity);
    QueryPerformanceCounter(&time_end);
    PrintTime(frequency,time_start,time_end);

    v->ops_->destroy(v);
    v2->ops_->destroy(v2);
    v3->ops_->destroy(v3);
    v4->ops_->destroy(v4);
    MM->status();
    return 0;
}