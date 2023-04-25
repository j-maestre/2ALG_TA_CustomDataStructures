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
//#include "EDK_MemoryManager/edk_memory_manager.h"
#include "EDK_MemoryManager/edk_platform_types.h"
//#include "common_def.h"
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

u16 data[20000];
u16 data_2[20000];

void* data_list[20000];
void* data_list_2[20000];


u16 capacity = 10000;
u16 size = 0;

int u16_size;

std::vector<u16> v;
std::vector<u16> v2;
std::list<u16> l;
std::list<u16> l2;

std::forward_list<u16> fl;
std::forward_list<u16> fl2;

double elapsed_time = 0.0f;
u32 repetitions = 10000;

void TESTBASE_generateDataForComparative() {

	u16_size = sizeof(u16);

	FILE *f;
	
	fopen_s(&f, "statics_std.csv", "w"); // Delete file if exist
	fclose(f);

	for(u16 i = 0; i < capacity*2; i++){
		u16 number = 5;
		u16 number2 = 9;
		data[i] = number;
		data_2[i] = number2;
	}


}

int64_t Millis() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec) / 1000000;
}

void FillVector(std::vector<u16> v, void* dataF[]){
  for(u32 i = 0; i < repetitions; i++){

    //v->ops_->insertFirst(v,dataF[i],size);
  }
}



void SaveResult(LARGE_INTEGER frequency, LARGE_INTEGER time_start, LARGE_INTEGER time_end, const char* operation, const char *header){
  	FILE *f;

	//try to open the file
	int err = fopen_s(&f, "statics_std.csv", "r");

	if (err == 0) 
	{  // If file can be open
		fclose(f);
		fclose(f);
		fopen_s(&f, "statics_std.csv", "a");
		//printf("File openen directly in Append\n");
	}
	else
	{  // If file can't be open
		fopen_s(&f, "statics_std.csv", "w"); //Create the file
		fclose(f);
		fopen_s(&f, "statics_std.csv", "a");
		//printf("File created and openened in Append\n");
	}


	char content[256];

	if (header != NULL){
		snprintf(content, sizeof(content), ";%s;\n\0",header);	
		fwrite(content, 1, strlen(content), f);
		snprintf(content, sizeof(content), ";Time Elapsed;Average Time\n\0");	
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
		v.insert(v.begin(),data[rep]);
		//v[rep] = data[rep];
    	data[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "STD Vector");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data[rep] = v[0];
		v.erase(v.begin());

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
		v.push_back(data[rep]);
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
    	data[rep] = v.back();
		v.pop_back();
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = v.size()/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		std::vector<u16>::iterator itPos = v.begin()+middle;
		v.insert(itPos,data[rep]);
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
		std::vector<u16>::iterator itPos = v.begin()+middle;
		data[rep] = v[middle];
		v.erase(itPos);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** Vector Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////


	for (u32 rep = 0; rep < repetitions; ++rep) {
		v.insert(v.begin(),data[rep]);
		v2.insert(v2.begin(),data[rep]);
	}


	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v.size(),v2.size());
	v.insert(
      v.end(),
      std::make_move_iterator(v2.begin()),
      std::make_move_iterator(v2.end())
    );
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v.size(),v2.size());
	v.insert(
      v.end(),
      std::make_move_iterator(v2.begin()),
      std::make_move_iterator(v2.end())
    );
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** Vector Concat with %d and %d size ***\n",v.size(),v2.size());
	v.insert(
      v.end(),
      std::make_move_iterator(v2.begin()),
      std::make_move_iterator(v2.end())
    );
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////


}

void calculateTimeForFunctionDDLList() {
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
		l.insert(l.begin(),data[rep]);
		//v[rep] = data[rep];
    	data[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "STD Double Linked List");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data[rep] = l.front();
		l.erase(l.begin());

  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Extract First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract First", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Insert Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		l.push_back(data[rep]);
    	data[rep] = NULL;
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Insert Last ***\n");
	PrintTime(frequency,time_start,time_end);
    SaveResult(frequency, time_start, time_end,"Insert Last", NULL);
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////
	// *** Extract Last *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
    	data[rep] = l.back();
		l.pop_back();
	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = l.size()/2;
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		std::list<u16>::iterator it = l.begin();
		advance(it, middle);
		l.insert(it,data[rep]);
    	data[rep] = NULL;
  }
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Insert At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert At", NULL);
	///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// *** Extract At *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		std::list<u16>::iterator it = l.begin();
		advance(it, middle);
		data[rep] = *it;
		l.erase(it);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** DLList Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////


	for (u32 rep = 0; rep < repetitions; ++rep) {
		l.insert(l.begin(),data[rep]);
		l2.insert(l2.begin(),data[rep]);
	}

	//merge()
	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
	printf("\n*** DLList Concat with %d and %d size ***\n",l.size(),l2.size());
	l.insert(l.end(), l2.begin(), l2.end());
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////
  	QueryPerformanceCounter(&time_start);

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** DLList Concat with %d and %d size ***\n",l.size(),l2.size());
	l.insert(l.end(), l2.begin(), l2.end());
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** DLList Concat with %d and %d size ***\n",l.size(),l2.size());
	l.insert(l.end(), l2.begin(), l2.end());
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////
	

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
		fl.push_front(data[rep]);
		//v[rep] = data[rep];
    	data[rep] = NULL;
	}
	// stop timer
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Insert First ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Insert First", "STD List");
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// *** Extract First *** //
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		data[rep] = fl.front();
		fl.pop_front();
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
		auto before_end = fl.before_begin();
		for (auto& _ : fl)
			++before_end;

		fl.insert_after(before_end,data[rep]);
		data[rep] = NULL;
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
			for (auto it = fl.before_begin(); std::next(it) != fl.end(); ++it) {
				if (std::next(it, 2) == fl.end()){
					data[rep] = 5;
					fl.erase_after(it);
					break;
				}
			}
		}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Extract Last ***\n");
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract Last", NULL);
	/////////////////////////////////////////////////////////////////////
	// *** Insert At *** //
	u16 middle = std::distance(fl.begin(),fl.end()) / 2; // It must be 0
	//u16 middle = 5000; 
	
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		middle = std::distance(fl.begin(),fl.end()) / 2; // It must be 0
		auto it = fl.before_begin();
		std::advance(it, middle);
		fl.insert_after(it,data[rep]);
    	data[rep] = NULL;
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
		auto it = fl.before_begin();
		middle = std::distance(fl.begin(),fl.end()) / 2; // It must be 0
		advance(it, middle);
		data[rep] = 5; 
		fl.erase_after(it);
  	}
	QueryPerformanceCounter(&time_end);
	printf("\n*** List Extract At position %d ***\n",middle);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Extract At", NULL);
	///////////////////////////////////////////////////////////////////////


	for (u32 rep = 0; rep < repetitions; ++rep) {
		fl.push_front(data[rep]);
		fl2.push_front(data[rep]);
	}

	//merge()
	/////////////////////////////////////////////////////////////////////
	// *** Concat 1 *** //
	printf("\n*** List Concat 1 with %d and %d size ***\n",std::distance(fl.begin(),fl.end()),std::distance(fl2.begin(),fl2.end()));
	fl.merge(fl2);
	//l.insert(l.end(), l2.begin(), l2.end());
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 1", NULL);
	///////////////////////////////////////////////////////////////////////
  	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		fl2.push_front(data[rep]);
	}

	/////////////////////////////////////////////////////////////////////
	// *** Concat 2 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** List Concat 2 with %d and %d size ***\n",std::distance(fl.begin(),fl.end()),std::distance(fl2.begin(),fl2.end()));
	//l.insert(l.end(), l2.begin(), l2.end());
	fl.merge(fl2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 2", NULL);
	///////////////////////////////////////////////////////////////////////

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep) {
		fl2.push_front(data[rep]);
	}
	/////////////////////////////////////////////////////////////////////
	// *** Concat 3 *** //
  	QueryPerformanceCounter(&time_start);
	printf("\n*** List Concat 3 with %d and %d size ***\n",std::distance(fl.begin(),fl.end()),std::distance(fl2.begin(),fl2.end()));
	//l.insert(l.end(), l2.begin(), l2.end());
	fl.merge(fl2);
	QueryPerformanceCounter(&time_end);
	PrintTime(frequency,time_start,time_end);
  	SaveResult(frequency, time_start, time_end,"Concat 3", NULL);
	///////////////////////////////////////////////////////////////////////
	

}

int main(int argc, char** argv) {
	srand(time(NULL));
	TESTBASE_generateDataForComparative();
	calculateTimeForFunction();
	calculateTimeForFunctionList();
	calculateTimeForFunctionDDLList();
	//MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	//MM->destroy();
	return 0;
}