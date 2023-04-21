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

void* data[10000];
Vector *v = NULL;
u16 capacity = 10000;
u16 size = sizeof(data);

double elapsed_time = 0.0f;
u32 repetitions = 10000;

void TESTBASE_generateDataForComparative() {
	//TODO some stuff
	// Generar informacion aleatoria
	// ORDEN -> create 1 vector de tamaño aleatorio. 
	// Insert first de tamaño variable de 1 hasta capacity.
	// Insert last de tamaño variable de 1 hasta capacity.
	// Insert at de tamaño variable en posicion aleatoria entre 1 hasta capacity.

	v = NULL;
	v = VECTOR_create(capacity);
	//v->ops_->insertFirst(v,data,sizeof(data));
	for(u16 i = 0; i < capacity; i++){
		u16 *number = MM->malloc(sizeof(u16));
		*number = 5;
		data[i] = number;
	}

}

int64_t Millis() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec) / 1000000;
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
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	

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
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->extractFirst(v);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract First ***\n");
	PrintTime(frequency,time_start,time_end);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Insert Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->insertLast(v,data[rep],size);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert Last ***\n");
	PrintTime(frequency,time_start,time_end);
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////
	// *** Extract Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->extractLast(v);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);

	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = v->capacity_/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions/2; ++rep) {
		v->ops_->insertAt(v,data[rep],size,middle);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Extract At *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		v->ops_->extractAt(v,middle);
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
	///////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////
	printf("\n*** Resize ***\n");
	QueryPerformanceCounter(&time_start);
	v->ops_->resize(v,capacity*2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
	///////////////////////////////////////////////////////////////////////


	


	for(u16 i = 0; i < capacity; i++){
		MM->free(data[i]);
	}
	//v->ops_->destroy(v);
	MM->free(v);
	
}

int main(int argc, char** argv) {
	srand(time(NULL));
	TESTBASE_generateDataForComparative();
	calculateTimeForFunction();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}