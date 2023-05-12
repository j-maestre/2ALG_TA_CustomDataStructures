// test_vector.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for vector ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

#include "./../tests/test_base.c"

const u16 kCapacityVector1 = 30;
const u16 kCapacityVector2 = 5;
const u16 kCapacityVector3 = 2;

int main() {
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// vector created just to have a reference to the operations
	Vector* v = NULL;
	v = Vector::Create(1);
	if (NULL == v) {
		printf("\n create returned a null node in vector for ops");
		return -1;
	}
	// vectors to work with
	Vector* vector_1 = NULL;
	Vector* vector_2 = NULL;
	Vector* vector_3 = NULL;
	vector_1 = Vector::Create(kCapacityVector1);
	if (NULL == vector_1) {
		printf("\n create returned a null node in vector_1\n");
		return -1;
	}
	vector_2 = Vector::Create(kCapacityVector2);
	if (NULL == vector_2) {
		printf("\n create returned a null node in vector_2\n");
		return -1;
	}
	vector_3 = Vector::Create(kCapacityVector3);
	if (NULL == vector_3) {
		printf("\n create returned a null node in vector_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + vector_1: %zu\n", sizeof(*vector_1));
	printf("	+ storage: %zu\n", sizeof(*(vector_1->data())));
	printf("  + vector_2: %zu\n", sizeof(*vector_2));
	printf("	+ storage: %zu\n", sizeof(*(vector_2->data())));
	printf("  + vector_3: %zu\n", sizeof(*vector_3));
	printf("	+ storage: %zu\n", sizeof(*(vector_3->data())));


	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = vector_1->reset();
	TESTBASE_printFunctionResult(vector_1, (u8*)"reset vector_1", error_type);

	error_type = vector_1->insertFirst(TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(vector_1, (u8*)"insertFirst vector_1", error_type);

	error_type = vector_1->reset();
	TESTBASE_printFunctionResult(vector_1, (u8*)"reset vector_1", error_type);

	if (False == vector_1->isEmpty())
	{
		printf("ERROR: isEmpty doesn't work correctly (vector_1)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertFirst vector_1\n");
	for (u16 i = 0; i < (kNumberOfStoragePtrTest_A / 2); ++i)
	{
		error_type = vector_1->insertFirst(TestData.storage_ptr_test_A[i], (strlen((const char*)TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8*)"insertFirst vector_1", error_type);
	}
	printf("vector_1:\n");
	vector_1->print();

	printf("\t insertLast vector_1\n");
	for (u16 i = (kNumberOfStoragePtrTest_A / 2); i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = vector_1->insertLast(TestData.storage_ptr_test_A[i], (strlen((const char*)TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8*)"insertLast vector_1", error_type);
	}
	printf("vector_1:\n");
	vector_1->print();

	printf("\t insertAt vector_1\n");
	u16 position = (kNumberOfStoragePtrTest_A / 2);
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = vector_1->insertAt(TestData.storage_ptr_test_B[i], (strlen((const char*)TestData.storage_ptr_test_B[i]) + 1), position);
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8*)"insertAt vector_1", error_type);
		position++;
	}
	printf("vector_1:\n");
	vector_1->print();

	printf("\t vector_2 insertAt\n");
	error_type = vector_2->insertAt(TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertAt vector_2", error_type);

	error_type = vector_2->insertAt(TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertAt vector_2 with NULL data", error_type);

	error_type = vector_2->insertAt(TestData.single_ptr_data_2, kSingleSizeData2, 0);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertAt vector_2", error_type);

	error_type = vector_2->insertAt(TestData.single_ptr_data_3, kSingleSizeData3, 4);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertAt vector_2", error_type);

	printf("vector_2:\n");
	vector_2->print();

	printf("\n\n# Test Insert\n");
	printf("\t insertLast vector_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == vector_3->isFull())
		{
			error_type = vector_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(vector_3, (u8*)"insertLast vector_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full vector (vector_3 capacity = %d)\n", vector_3->capacity());
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityVector3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (vector_3)\n");
	}
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t resize vector_3\n");
	error_type = vector_3->resize(10);
	TESTBASE_printFunctionResult(vector_3, (u8*)"resize vector_3", error_type);
	printf("vector_3:\n");
	vector_3->print();

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = vector_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(vector_3, (u8*)"insertLast vector_3", error_type);
	}
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test Extract\n");
	printf("\t extractAt vector_3\n");
	position = 2;
	TestData.storage_ptr_test_C[position] = vector_3->extractAt(position);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", position);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], position);
	position++;
	TestData.storage_ptr_test_C[position] = vector_3->extractAt(2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], 2);
	position++;
	TestData.storage_ptr_test_C[position] = vector_3->extractAt(2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], 2);

	printf("vector_3:\n");
	vector_3->print();

	printf("\t extractFirst vector_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = vector_3->extractFirst();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at first position\n");
		else
			printf("extracted \"%s\" at first position in vector_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("vector_3:\n");
	vector_3->print();
	printf("\t extractLast vector_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = vector_3->extractLast();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at Last position\n");
		else
			printf("extracted \"%s\" at last position in vector_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("vector_3:\n");
	vector_3->print();

	void* data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == vector_3->isEmpty())
		{
			data = vector_3->extractLast();
			MM->free(data);
			printf("ERROR: Trying to extract an element in an empty vector (vector_3 length = %d)\n", vector_3->length());
			extract_errors++;
		}
	}
	if (extract_errors > 0)
	{
		printf("  ==> ERROR: isEmpty doesn't work correctly (vector_3)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertLast vector_3\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = vector_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(vector_3, (u8*)"insertLast vector_3", error_type);
	}
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test First\n");
	printf("\t first vector_1\n");
	data = vector_1->first();
	if (NULL == data)
		printf("First in vector_1: NULL\n");
	else
		printf("First in vector_1: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at vector_3 (position %d)\n", position);
	data = vector_3->at(1);
	if (NULL == data)
		printf("At in vector_3: NULL\n");
	else
		printf("At in vector_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last vector_1\n");
	data = vector_1->last();
	if (NULL == data)
		printf("Last in vector_1: NULL\n");
	else
		printf("Last in vector_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t vector_1: [Capacity = %d] - [Length  = %d]\n", vector_1->capacity(), vector_1->length());
	printf("\t vector_2: [Capacity = %d] - [Length  = %d]\n", vector_2->capacity(), vector_2->length());
	printf("\t vector_3: [Capacity = %d] - [Length  = %d]\n", vector_3->capacity(), vector_3->length());

	printf("\n\n# Test Concat\n");
	printf("\t concat vector_1 + vector_3\n");
	error_type = vector_1->concat(vector_3);
	TESTBASE_printFunctionResult(vector_1, (u8*)"concat vector_1 + vector_3", error_type);
	printf("vector_1:\n");
	vector_1->print();
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test Length\n");
	printf("\t Length vector_1 = %d \n", vector_1->length());
	printf("\t Length vector_2 = %d \n", vector_2->length());
	printf("\t Length vector_3 = %d \n", vector_3->length());

	printf("\n\n# Test Reset\n");
	error_type = vector_3->reset();
	TESTBASE_printFunctionResult(vector_3, (u8*)"reset vector_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length vector_1 = %d \n", vector_1->length());
	printf("\t Length vector_2 = %d \n", vector_2->length());
	printf("\t Length vector_3 = %d \n", vector_3->length());


	printf("\n\n# Test First\n");
	printf("\t first vector_3\n");
	data = vector_3->first();
	if (NULL == data)
		printf("First in vector_3: NULL\n");
	else
		printf("ERROR: First in vector_3: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at vector_3 (position %d)\n", position);
	data = vector_3->at(1);
	if (NULL == data)
		printf("At in vector_3: NULL\n");
	else
		printf("ERROR: At in vector_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last vector_3\n");
	data = vector_3->last();
	if (NULL == data)
		printf("Last in vector_3: NULL\n");
	else
		printf("ERROR: Last in vector_3: \"%s\"\n", data);


	printf("\n\n# Test Concat\n");
	printf("\t concat vector_3 + vector_2\n");
	error_type = vector_3->concat(vector_2);
	TESTBASE_printFunctionResult(vector_3, (u8*)"concat vector_3 + vector_2", error_type);
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test Destroy\n");
	printf("\t vector_2 Destroy\n");
	error_type = vector_2->destroy();
	vector_2 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8*)"destroy vector_2", error_type);
	printf("vector_2:\n");
	vector_2->print();

	printf("\t vector_3 Destroy\n");
	error_type = vector_3->destroy();
	vector_3 = NULL;
	TESTBASE_printFunctionResult(vector_3, (u8*)"destroy vector_3", error_type);
	printf("vector_3:\n");
	vector_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t vector_1 resize\n");
	error_type = vector_1->resize(3);
	TESTBASE_printFunctionResult(vector_1, (u8*)"resize vector_1", error_type);
	printf("vector_1:\n");
	vector_1->print();

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	printf("\n\n# Test Create\n");
	vector_2 = Vector::Create(0);
	if (NULL != vector_2) {
		printf("ERROR: trying to create vector_2 with 0 capacity\n");
		return -1;
	}

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = vector_2->insertFirst(data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertFirst vector_2 (NOT VALID)", error_type);
	error_type = vector_2->insertLast(data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertLast vector_2 (NOT VALID)", error_type);
	error_type = vector_2->insertAt(data, kSingleSizeBigData, 1);
	TESTBASE_printFunctionResult(vector_2, (u8*)"insertAt vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test First\n");
	printf("\t first vector_2\n");
	data = vector_2->first();
	if (NULL != data)
		printf("ERROR: First in vector_2 is not NULL\n");

	printf("\n\n# Test At\n");
	printf("\t at vector_2 (position 1)\n");
	data = vector_2->at(1);
	if (NULL != data)
		printf("ERROR: At in vector_2 is not NULL\n");

	printf("\n\n# Test Last\n");
	printf("\t last vector_2\n");
	data = vector_2->last();
	if (NULL != data)
		printf("ERROR: Last in vector_2 is not NULL\n");


	printf("\n\n# Test Extract\n");
	data = vector_2->extractFirst();
	if (NULL != data)
	{
		printf("ERROR: trying to extractFirst from an empty vector\n");
	}
	data = vector_2->extractLast();
	if (NULL != data)
	{
		printf("ERROR: trying to extractLast from an empty vector\n");
	}
	data = vector_2->extractAt(1);
	if (NULL != data)
	{
		printf("ERROR: trying to extractAt from an empty vector\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat vector_1 + vector_2\n");
	error_type = vector_1->concat(vector_2);
	TESTBASE_printFunctionResult(vector_1, (u8*)"concat vector_1 + vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = vector_2->resize(5);
	TESTBASE_printFunctionResult(vector_2, (u8*)"resize vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = vector_2->reset();
	TESTBASE_printFunctionResult(vector_2, (u8*)"reset vector_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = vector_2->destroy();
	TESTBASE_printFunctionResult(vector_2, (u8*)"destroy vector_2 (NOT VALID)", error_type);
	error_type = vector_3->destroy();
	TESTBASE_printFunctionResult(vector_3, (u8*)"destroy vector_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = vector_1->destroy();
	TESTBASE_printFunctionResult(vector_1, (u8*)"destroy vector_1", error_type);
	error_type = v->destroy();
	TESTBASE_printFunctionResult(v, (u8*)"destroy Vector Operations", error_type);

	printf("\nAt this point, it must be only one block of %d bytes waiting to be freed\n\n", kSingleSizeBigData);
	MM->status();
	TESTBASE_freeDataForTest();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
