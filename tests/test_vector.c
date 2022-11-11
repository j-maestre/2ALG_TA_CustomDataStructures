// test_vector.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for vector ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_vector.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

#include "./../tests/test_base.c"

const u16 kCapacityVector1 = 30;
const u16 kCapacityVector2 = 5;
const u16 kCapacityVector3 = 2;

int main() {
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// vector created just to have a reference to the operations
	Vector *v = NULL;
	v = VECTOR_create(1);
	if (NULL == v) {
		printf("\n create returned a null node in vector for ops");
		return -1;
	}
	// vectors to work with
	Vector *vector_1 = NULL;
	Vector *vector_2 = NULL;
	Vector *vector_3 = NULL;
	vector_1 = VECTOR_create(kCapacityVector1);
	if (NULL == vector_1) {
		printf("\n create returned a null node in vector_1\n");
		return -1;
	}
	vector_2 = VECTOR_create(kCapacityVector2);
	if (NULL == vector_2) {
		printf("\n create returned a null node in vector_2\n");
		return -1;
	}
	vector_3 = VECTOR_create(kCapacityVector3);
	if (NULL == vector_3) {
		printf("\n create returned a null node in vector_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + vector_1: %zu\n", sizeof(*vector_1));
	printf("	+ storage: %zu\n", sizeof(*(vector_1->storage_)));
	printf("  + vector_2: %zu\n", sizeof(*vector_2));
	printf("	+ storage: %zu\n", sizeof(*(vector_2->storage_)));
	printf("  + vector_3: %zu\n", sizeof(*vector_3));
	printf("	+ storage: %zu\n", sizeof(*(vector_3->storage_)));


	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = v->ops_->reset(vector_1);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"reset vector_1", error_type);

	error_type = v->ops_->insertFirst(vector_1, TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(vector_1, (u8 *)"insertFirst vector_1", error_type);

	error_type = v->ops_->reset(vector_1);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"reset vector_1", error_type);

	if (False == v->ops_->isEmpty(vector_1))
	{
		printf("ERROR: isEmpty doesn't work correctly (vector_1)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertFirst vector_1\n");
	for (u16 i = 0; i < (kNumberOfStoragePtrTest_A / 2); ++i)
	{
		error_type = v->ops_->insertFirst(vector_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8 *)"insertFirst vector_1", error_type);
	}
	printf("vector_1:\n");
	v->ops_->print(vector_1);

	printf("\t insertLast vector_1\n");
	for (u16 i = (kNumberOfStoragePtrTest_A / 2); i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = v->ops_->insertLast(vector_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8 *)"insertLast vector_1", error_type);
	}
	printf("vector_1:\n");
	v->ops_->print(vector_1);

	printf("\t insertAt vector_1\n");
	u16 position = (kNumberOfStoragePtrTest_A / 2);
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = v->ops_->insertAt(vector_1, TestData.storage_ptr_test_B[i], (strlen(TestData.storage_ptr_test_B[i]) + 1), position);
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(vector_1, (u8 *)"insertAt vector_1", error_type);
		position++;
	}
	printf("vector_1:\n");
	v->ops_->print(vector_1);

	printf("\t vector_2 insertAt\n");
	error_type = v->ops_->insertAt(vector_2, TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertAt vector_2", error_type);

	error_type = v->ops_->insertAt(vector_2, TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertAt vector_2 with NULL data", error_type);

	error_type = v->ops_->insertAt(vector_2, TestData.single_ptr_data_2, kSingleSizeData2, 0);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertAt vector_2", error_type);

	error_type = v->ops_->insertAt(vector_2, TestData.single_ptr_data_3, kSingleSizeData3, 4);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertAt vector_2", error_type);

	printf("vector_2:\n");
	v->ops_->print(vector_2);

	printf("\n\n# Test Insert\n");
	printf("\t insertLast vector_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == v->ops_->isFull(vector_3))
		{
			error_type = v->ops_->insertLast(vector_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(vector_3, (u8 *)"insertLast vector_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full vector (vector_3 capacity = %d)\n", v->ops_->capacity(vector_3));
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityVector3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (vector_3)\n");
	}
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test Resize\n");
	printf("\t resize vector_3\n");
	error_type = v->ops_->resize(vector_3, 10);
	TESTBASE_printFunctionResult(vector_3, (u8 *)"resize vector_3", error_type);
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = v->ops_->insertLast(vector_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(vector_3, (u8 *)"insertLast vector_3", error_type);
	}
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test Extract\n");
	printf("\t extractAt vector_3\n");
	position = 2;
	TestData.storage_ptr_test_C[position] = v->ops_->extractAt(vector_3, position);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", position);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], position);
	position++;
	TestData.storage_ptr_test_C[position] = v->ops_->extractAt(vector_3, 2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], 2);
	position++;
	TestData.storage_ptr_test_C[position] = v->ops_->extractAt(vector_3, 2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in vector_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in vector_3\n", TestData.storage_ptr_test_C[position], 2);

	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\t extractFirst vector_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = v->ops_->extractFirst(vector_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at first position\n");
		else
			printf("extracted \"%s\" at first position in vector_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("vector_3:\n");
	v->ops_->print(vector_3);
	printf("\t extractLast vector_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = v->ops_->extractLast(vector_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at Last position\n");
		else
			printf("extracted \"%s\" at last position in vector_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == v->ops_->isEmpty(vector_3))
		{
			data = v->ops_->extractLast(vector_3);
			MM->free(data);
			printf("ERROR: Trying to extract an element in an empty vector (vector_3 length = %d)\n", v->ops_->length(vector_3));
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
		error_type = v->ops_->insertLast(vector_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(vector_3, (u8 *)"insertLast vector_3", error_type);
	}
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test First\n");
	printf("\t first vector_1\n");
	data = v->ops_->first(vector_1);
	if (NULL == data)
		printf("First in vector_1: NULL\n");
	else
		printf("First in vector_1: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at vector_3 (position %d)\n", position);
	data = v->ops_->at(vector_3, 1);
	if (NULL == data)
		printf("At in vector_3: NULL\n");
	else
		printf("At in vector_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last vector_1\n");
	data = v->ops_->last(vector_1);
	if (NULL == data)
		printf("Last in vector_1: NULL\n");
	else
		printf("Last in vector_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t vector_1: [Capacity = %d] - [Length  = %d]\n", v->ops_->capacity(vector_1), v->ops_->length(vector_1));
	printf("\t vector_2: [Capacity = %d] - [Length  = %d]\n", v->ops_->capacity(vector_2), v->ops_->length(vector_2));
	printf("\t vector_3: [Capacity = %d] - [Length  = %d]\n", v->ops_->capacity(vector_3), v->ops_->length(vector_3));

	printf("\n\n# Test Concat\n");
	printf("\t concat vector_1 + vector_3\n");
	error_type = v->ops_->concat(vector_1, vector_3);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"concat vector_1 + vector_3", error_type);
	printf("vector_1:\n");
	v->ops_->print(vector_1);
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test Length\n");
	printf("\t Length vector_1 = %d \n", v->ops_->length(vector_1));
	printf("\t Length vector_2 = %d \n", v->ops_->length(vector_2));
	printf("\t Length vector_3 = %d \n", v->ops_->length(vector_3));

	printf("\n\n# Test Reset\n");
	error_type = v->ops_->reset(vector_3);
	TESTBASE_printFunctionResult(vector_3, (u8 *)"reset vector_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length vector_1 = %d \n", v->ops_->length(vector_1));
	printf("\t Length vector_2 = %d \n", v->ops_->length(vector_2));
	printf("\t Length vector_3 = %d \n", v->ops_->length(vector_3));


	printf("\n\n# Test First\n");
	printf("\t first vector_3\n");
	data = v->ops_->first(vector_3);
	if (NULL == data)
		printf("First in vector_3: NULL\n");
	else
		printf("ERROR: First in vector_3: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at vector_3 (position %d)\n", position);
	data = v->ops_->at(vector_3, 1);
	if (NULL == data)
		printf("At in vector_3: NULL\n");
	else
		printf("ERROR: At in vector_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last vector_3\n");
	data = v->ops_->last(vector_3);
	if (NULL == data)
		printf("Last in vector_3: NULL\n");
	else
		printf("ERROR: Last in vector_3: \"%s\"\n", data);


	printf("\n\n# Test Concat\n");
	printf("\t concat vector_3 + vector_2\n");
	error_type = v->ops_->concat(vector_3, vector_2);
	TESTBASE_printFunctionResult(vector_3, (u8 *)"concat vector_3 + vector_2", error_type);
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test Destroy\n");
	printf("\t vector_2 Destroy\n");
	error_type = v->ops_->destroy(vector_2);
	vector_2 = NULL;
	TESTBASE_printFunctionResult(vector_2, (u8 *)"destroy vector_2", error_type);
	printf("vector_2:\n");
	v->ops_->print(vector_2);

	printf("\t vector_3 Destroy\n");
	error_type = v->ops_->destroy(vector_3);
	vector_3 = NULL;
	TESTBASE_printFunctionResult(vector_3, (u8 *)"destroy vector_3", error_type);
	printf("vector_3:\n");
	v->ops_->print(vector_3);

	printf("\n\n# Test Resize\n");
	printf("\t vector_1 resize\n");
	error_type = v->ops_->resize(vector_1, 3);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"resize vector_1", error_type);
	printf("vector_1:\n");
	v->ops_->print(vector_1);

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	printf("\n\n# Test Create\n");
	vector_2 = VECTOR_create(0);
	if (NULL != vector_2) {
		printf("ERROR: trying to create vector_2 with 0 capacity\n");
		return -1;
	}

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = v->ops_->insertFirst(vector_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertFirst vector_2 (NOT VALID)", error_type);
	error_type = v->ops_->insertLast(vector_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertLast vector_2 (NOT VALID)", error_type);
	error_type = v->ops_->insertAt(vector_2, data, kSingleSizeBigData, 1);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"insertAt vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test First\n");
	printf("\t first vector_2\n");
	data = v->ops_->first(vector_2);
	if (NULL != data)
		printf("ERROR: First in vector_2 is not NULL\n");

	printf("\n\n# Test At\n");
	printf("\t at vector_2 (position 1)\n");
	data = v->ops_->at(vector_2, 1);
	if (NULL != data)
		printf("ERROR: At in vector_2 is not NULL\n");

	printf("\n\n# Test Last\n");
	printf("\t last vector_2\n");
	data = v->ops_->last(vector_2);
	if (NULL != data)
		printf("ERROR: Last in vector_2 is not NULL\n");


	printf("\n\n# Test Extract\n");
	data = v->ops_->extractFirst(vector_2);
	if (NULL != data)
	{
		printf("ERROR: trying to extractFirst from an empty vector\n");
	}
	data = v->ops_->extractLast(vector_2);
	if (NULL != data)
	{
		printf("ERROR: trying to extractLast from an empty vector\n");
	}
	data = v->ops_->extractAt(vector_2, 1);
	if (NULL != data)
	{
		printf("ERROR: trying to extractAt from an empty vector\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat vector_1 + vector_2\n");
	error_type = v->ops_->concat(vector_1, vector_2);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"concat vector_1 + vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = v->ops_->resize(vector_2, 5);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"resize vector_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = v->ops_->reset(vector_2);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"reset vector_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = v->ops_->destroy(vector_2);
	TESTBASE_printFunctionResult(vector_2, (u8 *)"destroy vector_2 (NOT VALID)", error_type);
	error_type = v->ops_->destroy(vector_3);
	TESTBASE_printFunctionResult(vector_3, (u8 *)"destroy vector_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = v->ops_->destroy(vector_1);
	TESTBASE_printFunctionResult(vector_1, (u8 *)"destroy vector_1", error_type);
	error_type = v->ops_->destroy(v);
	TESTBASE_printFunctionResult(v, (u8 *)"destroy Vector Operations", error_type);

	printf("\nAt this point, it must be only one block of %d bytes waiting to be freed\n\n", kSingleSizeBigData);
	MM->status();
	TESTBASE_freeDataForTest();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
