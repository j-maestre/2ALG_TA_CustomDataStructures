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

void* data[20000];
void* data_2[20000];
Vector *v = NULL;
Vector *v2 = NULL;
u16 capacity = 10000;
u16 size = 0;


double elapsed_time = 0.0f;
u32 repetitions = 10000;

void TESTBASE_generateDataForComparative() {
	//TODO some stuff
	// Generar informacion aleatoria
	// ORDEN -> create 1 vector de tamaño aleatorio. 
	// Insert first de tamaño variable de 1 hasta capacity.
	// Insert last de tamaño variable de 1 hasta capacity.
	// Insert at de tamaño variable en posicion aleatoria entre 1 hasta capacity.

	size = sizeof(u16);


	v = NULL;
	v = VECTOR_create(capacity);
	//v->ops_->insertFirst(v,data,sizeof(data));
	for(u16 i = 0; i < capacity*2; i++){
		u16 *number = MM->malloc(sizeof(u16));
		u16 *number2 = MM->malloc(sizeof(u16));
		*number = 5;
		*number2 = 9;
		data[i] = number;
		data_2[i] = number2;
	}

}

int64_t Millis() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec) / 1000000;
}

void FillVector(Vector *v, void* data[]){
  for(u32 i = 0; i < repetitions; i++){
    v->ops_->insertFirst(v,data[i],size);
  }
}

void SaveResult(LARGE_INTEGER frequency, LARGE_INTEGER time_start, LARGE_INTEGER time_end, const char* operation, const char *header){
  	FILE *f;

	//try to open the file
	int err = fopen_s(&f, "statics.csv", "r");

	if (err == 0) 
	{  // If file can be open
		fclose(f);
		fopen_s(&f, "statics.csv", "a");
		printf("File openen directly in Append\n");
	}
	else
	{  // If file can't be open
		fopen_s(&f, "statics.csv", "w"); //Create the file
		fclose(f);
		fopen_s(&f, "statics.csv", "a");
		printf("File created and openened in Append\n");
	}


	char content[256];

	if (header != NULL){
		snprintf(content, sizeof(content), ";%s;\n\0", header);	
		fwrite(content, 1, strlen(content), f);
		snprintf(content, sizeof(content), ";Time Elapsed;Average Time\n\0", header);	
		fwrite(content, 1, strlen(content), f);
		printf("*** HEADER ***\n %s\n",content);
	}

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	double average_time = elapsed_time / repetitions;

	if (content != NULL)
	{
		snprintf(content, sizeof(content), "%s;%.4f;%.4f\n\0", operation, elapsed_time, average_time);
		printf("*** CONTENT  ***\n %s\n",content);
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