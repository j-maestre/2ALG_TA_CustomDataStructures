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

void swap(u16 first, u16 second){
  

}

 
int partition(Vector *v, u16 start, u16 end)
{
 
    u16 pivot = v->ops_->at(v,start);
 
    u16 count = 0;
    for (u16 i = start + 1; i <= end; i++) {
        if (v->ops_->at(v,i) <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    u16 pivotIndex = start + count;
    swap(v->ops_->at(v,pivotIndex), v->ops_->at(v, start));
 
    // Sorting left and right parts of the pivot element
    u16 i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (v->ops_->at(v,i) <= pivot) {
            i++;
        }
 
        while (v->ops_->at(v,j) > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
          swap(i++, j--);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(Vector *v, u16 start, u16 end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    u16 p = partition(v, start, end);
 
    // Sorting the left part
    quickSort(v, start, p - 1);
 
    // Sorting the right part
    quickSort(v, p + 1, end);
}
 
u16 capacity;
u16 data[5000];
u16 data2[5000];
u16 max_range;
void InitDataForTest(){
  srand(time(NULL));
  capacity = 5000;
  max_range = 150;
  v = NULL;
  v = VECTOR_create(capacity);

  for(u16 i = 0; i < capacity; i++){
		u16 *number = MM->malloc(sizeof(u16));
		u16 *number2 = MM->malloc(sizeof(u16));
    int r = rand()%max_range;
  	*number = r;
  	*number2 = r;
		data[i] = number;
		data2[i] = number2;
    v->ops_->insertFirst(v,number,sizeof(u16));

	}
}

int main()
{
    InitDataForTest();
    int arr[] = { 9, 3, 4, 2, 1, 8 };
    u16 n = 6;
 
    quickSort(v, 0, max_range - 1);
 
    for (u16 i = 0; i < max_range; i++) {
      printf("%d - ",v->ops_->at(v,i));
       // cout << arr[i] << " ";
    }
 
    return 0;
}