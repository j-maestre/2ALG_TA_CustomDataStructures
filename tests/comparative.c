// comparative.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// File for comparative of ADTs

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
//#include <iostream>
//#include <vector>

void* data[20000];
void* data_2[20000];

void* data_list[20000];
void* data_list_2[20000];

void* data_dlist[20000];
void* data_dlist_2[20000];

Vector *v = NULL;
Vector *v2 = NULL;
List * list;
List * list2;
DLList * dlist;
DLList * dlist2;
u16 capacity = 10000;
u16 size = 0;

int u16_size;

//std::vector<u16> std_vector;

double elapsed_time = 0.0f;
u32 repetitions = 10000;

void TESTBASE_generateDataForComparative() {

	u16_size = sizeof(u16);

	FILE *f;
	
	fopen_s(&f, "statics.csv", "w"); // Delete file if exist
	fclose(f);

	size = sizeof(u16);
	
	v = NULL;
	v = VECTOR_create(capacity);
	list = NULL;
	list = LIST_create(capacity);
	dlist = NULL;
	dlist = DLLIST_create(capacity);
	for(u16 i = 0; i < capacity*2; i++){
		u16 *number = MM->malloc(sizeof(u16));
		u16 *number2 = MM->malloc(sizeof(u16));
		*number = 5;
		*number2 = 9;
		data[i] = number;
		data_2[i] = number2;
	}

	for(u16 i = 0; i < capacity * 2; i++){
		u16 *number = MM->malloc(sizeof(u16));
		u16 *number2 = MM->malloc(sizeof(u16));

		*number = 6;
		*number2 = 33;

		data_list[i] = number;
		data_list_2[i] = number2;
	}
	for(u16 i = 0; i < capacity * 2; i++){
		u16 *number = MM->malloc(sizeof(u16));
		u16 *number2 = MM->malloc(sizeof(u16));

		*number = 6;
		*number2 = 33;

		data_dlist[i] = number;
		data_dlist_2[i] = number2;
	}

}

int64_t Millis() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec) / 1000000;
}

void FillVector(Vector *v, void* dataF[]){
  for(u32 i = 0; i < repetitions; i++){
    v->ops_->insertFirst(v,dataF[i],size);
  }
}

void FillList(List *l, void* dataF[]){
  for(u32 i = 0; i < repetitions; i++){
    l->ops_->insertFirst(l,dataF[i],size);
  }
}

void FillDList(DLList *dl, void* dataF[]){
  for(u32 i = 0; i < repetitions; i++){
    dl->ops_->insertFirst(dl,dataF[i],size);
  }
}

void SaveResult(LARGE_INTEGER frequency, LARGE_INTEGER time_start, LARGE_INTEGER time_end, const char* operation, const char *header){
  	FILE *f;

	//try to open the file
	int err = fopen_s(&f, "statics.csv", "r");

	if (err == 0) 
	{  // If file can be open
		fclose(f);
		fclose(f);
		fopen_s(&f, "statics.csv", "a");
		//printf("File openen directly in Append\n");
	}
	else
	{  // If file can't be open
		fopen_s(&f, "statics.csv", "w"); //Create the file
		fclose(f);
		fopen_s(&f, "statics.csv", "a");
		//printf("File created and openened in Append\n");
	}


	char content[256];

	if (header != NULL){
		snprintf(content, sizeof(content), ";%s;\n\0",header);	
		//snprintf(content, sizeof(content), ";%s;;STD %s\n\0", header,header);	
		fwrite(content, 1, strlen(content), f);
		snprintf(content, sizeof(content), ";Time Elapsed;Average Time;\n\0");	
		//snprintf(content, sizeof(content), ";Time Elapsed;Average Time;Time Elapsed;Average Time\n\0");	
		fwrite(content, 1, strlen(content), f);
	}

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	double average_time = elapsed_time / repetitions;

	if (content != NULL)
	{
		snprintf(content, sizeof(content), "%s;%.4f;%.4f\n\0", operation, elapsed_time, average_time);
		fwrite(content, 1, strlen(content), f);
	}

	fclose(f);
}

void PrintTime(LARGE_INTEGER frequency, LARGE_INTEGER time_start, LARGE_INTEGER time_end){
	///////////////////////////////////////////////////////////////////////
	// compute the elapsed time in microseconds
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	printf("Elapsed time: %f ms\n", elapsed_time);
	///////////////////////////////////////////////////////////////////////
	// compute the average time
	double average_time = elapsed_time / repetitions;
	printf("Average time: %f ms\n", average_time);
	///////////////////////////////////////////////////////////////////////

}

void calculateTimeForFunction() {
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval, 
	

	///////////////////////////////////////////////////////////////////////
	// Frequency: ticks per second
	QueryPerformanceFrequency(&frequency);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Insert First *** //
	// Meassurement time
	// start timer
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->insertFirst(v,data[rep],size);
    	data[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "Vector");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data[rep] = v->ops_->extractFirst(v);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract First", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Insert Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->insertLast(v,data[rep],size);
    data[rep] = NULL;
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert Last ***\n");
	PrintTime(frequency,time_start,time_end);
    SaveResult(frequency, time_start, time_end,"Insert Last", NULL);
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////
	// *** Extract Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    data[rep] = v->ops_->extractLast(v);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = v->capacity_/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->insertAt(v,data[rep],size,middle);
    data[rep] = NULL;
  }
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Extract At *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    	data[rep] = v->ops_->extractAt(v,0);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
  	v2 = NULL;
  	v2 = VECTOR_create(capacity*2);
  	FillVector(v2,data_2);
  
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v->capacity_,v2->capacity_);
  	// Aqui arriba lo mismo
  	v->ops_->concat(v,v2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v->capacity_,v2->capacity_);
  	// Lo concateno, osea, copio los datos del v2 y los pongo al final del v1
  	v->ops_->concat(v,v2);
  	//v->ops_->reset(v);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v->capacity_,v2->capacity_);
  	// Lo concateno, osea, copio los datos del v2 y los pongo al final del v1
  	v->ops_->concat(v,v2);
  	//v->ops_->reset(v);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////


	for (u32 i = 0; i < capacity*2; i++) {
		MM->free(data[i]);
		MM->free(data_2[i]);
	}


	v->ops_->destroy(v);
  	v2->ops_->softReset(v2);
	v2->ops_->destroy(v2);
}

void calculateTimeForFunctionList() {
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval, 
	

	///////////////////////////////////////////////////////////////////////
	// Frequency: ticks per second
	QueryPerformanceFrequency(&frequency);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Insert First *** //
	// Meassurement time
	// start timer
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 rep = 0; rep < repetitions; ++rep) {
		list->ops_->insertFirst(list,data_list[rep],size);
    	data_list[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "List");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data_list[rep] = list->ops_->extractFirst(list);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Extract First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract First", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Insert Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		list->ops_->insertLast(list,data_list[rep],size);
    	data_list[rep] = NULL;
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Insert Last ***\n");
	PrintTime(frequency,time_start,time_end);
    SaveResult(frequency, time_start, time_end,"Insert Last", NULL);
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////
	// *** Extract Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    data_list[rep] = list->ops_->extractLast(list);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = list->capacity_/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		list->ops_->insertAt(list,data_list[rep],size,middle);
    	data_list[rep] = NULL;
  }
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Insert At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Extract At *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    	data_list[rep] = list->ops_->extractAt(list,0);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
	list2 = NULL;
  	list2 = LIST_create(capacity);
	FillList(list2,data_list_2);
  	
  
  	QueryPerformanceCounter(&time_start);
	printf("\n*** List Concat with %d and %d size ***\n",list->capacity_,list2->capacity_);
  	list->ops_->concat(list,list2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** List Concat with %d and %d size ***\n",list->capacity_,list2->capacity_);
  	list->ops_->concat(list,list2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** List Concat with %d and %d size ***\n",list->capacity_,list2->capacity_);
  	list->ops_->concat(list,list2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////


	for (u32 i = 0; i < capacity*2; i++) {
		MM->free(data_list[i]);
		MM->free(data_list_2[i]);
	}

	//list->ops_->softReset(list);
	list->ops_->destroy(list);
  	list2->ops_->softReset(list2);
	list2->ops_->destroy(list2);
}

void calculateTimeForFunctionDList() {
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval, 
	

	///////////////////////////////////////////////////////////////////////
	// Frequency: ticks per second
	QueryPerformanceFrequency(&frequency);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Insert First *** //
	// Meassurement time
	// start timer
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 rep = 0; rep < repetitions; ++rep) {
		dlist->ops_->insertFirst(dlist,data_dlist[rep],size);
    	data_dlist[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n***  DList Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "DList");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data_dlist[rep] = dlist->ops_->extractFirst(dlist);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DList Extract First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract First", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Insert Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		dlist->ops_->insertLast(dlist,data_dlist[rep],size);
    	data_dlist[rep] = NULL;
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DList Insert Last ***\n");
	PrintTime(frequency,time_start,time_end);
    SaveResult(frequency, time_start, time_end,"Insert Last", NULL);
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////
	// *** Extract Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    data_dlist[rep] = dlist->ops_->extractLast(dlist);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DList Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = dlist->capacity_/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		dlist->ops_->insertAt(dlist,data_dlist[rep],size,middle);
    	data_dlist[rep] = NULL;
  }
	QueryPerformanceCounter(&time_end);
	printf("\n*** DList Insert At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Extract At *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    	data_dlist[rep] = dlist->ops_->extractAt(dlist,0);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DList Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
	dlist2 = NULL;
  	dlist2 = DLLIST_create(capacity);
	
	FillDList(dlist2,data_dlist_2);
  	
  
  	QueryPerformanceCounter(&time_start);
	printf("\n*** DList Concat with %d and %d size ***\n",dlist->capacity_,dlist2->capacity_);
  	dlist->ops_->concat(dlist,dlist2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** DList Concat with %d and %d size ***\n",dlist->capacity_,dlist2->capacity_);
  	dlist->ops_->concat(dlist,dlist2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** DList Concat with %d and %d size ***\n",dlist->capacity_,dlist2->capacity_);
  	dlist->ops_->concat(dlist,dlist2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////


for (u32 i = 0; i < capacity*2; i++) {
		MM->free(data_dlist[i]);
		MM->free(data_dlist_2[i]);
	}

	//dlist->ops_->softReset(dlist);
	dlist->ops_->destroy(dlist);

  	dlist2->ops_->softReset(dlist2);
	dlist2->ops_->destroy(dlist2);
}

int main(int argc, char** argv) {
	srand(time(NULL));
	TESTBASE_generateDataForComparative();
	calculateTimeForFunction();
	calculateTimeForFunctionList();
	calculateTimeForFunctionDList();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}