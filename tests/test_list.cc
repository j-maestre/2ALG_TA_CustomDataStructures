// test_list.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for list ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

#include "./../tests/test_base.c"

const u16 kCapacityList1 = 30;
const u16 kCapacityList2 = 5;
const u16 kCapacityList3 = 2;

int main() {
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// list created just to have a reference to the operations
	List *ls = NULL;
	ls = List::Create(1);
	if (NULL == ls) {
		printf("\n create returned a null node in list for ops");
		return -1;
	}
	// vectors to work with
	List *list_1 = NULL;
	List *list_2 = NULL;
	List *list_3 = NULL;
	list_1 = List::Create(kCapacityList1);
	if (NULL == list_1) {
		printf("\n create returned a null node in list_1\n");
		return -1;
	}
	list_2 = List::Create(kCapacityList2);
	if (NULL == list_2) {
		printf("\n create returned a null node in list_2\n");
		return -1;
	}
	list_3 = List::Create(kCapacityList3);
	if (NULL == list_3) {
		printf("\n create returned a null node in list_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + list_1: %zu\n", sizeof(*list_1));
	printf("  + list_2: %zu\n", sizeof(*list_2));
	printf("  + list_3: %zu\n", sizeof(*list_3));

	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = list_1->reset();
	TESTBASE_printFunctionResult(list_1, (u8 *)"reset list_1", error_type);

	error_type = list_1->insertFirst(TestData.single_ptr_data_4, (u16) kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(list_1, (u8 *)"insertFirst list_1", error_type);

	error_type = list_1->reset();
	TESTBASE_printFunctionResult(list_1, (u8 *)"reset list_1", error_type);

	if (False == list_1->isEmpty())
	{
		printf("ERROR: isEmpty doesn't work correctly (list_1)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertFirst list_1\n");
	for (u16 i = 0; i < (kNumberOfStoragePtrTest_A / 2); ++i)
	{
		error_type = list_1->insertFirst(TestData.storage_ptr_test_A[i], (strlen((const char*)TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertFirst list_1", error_type);
	}
	printf("list_1:\n");
	list_1->print();

	printf("\t insertLast list_1\n");
	for (u16 i = (kNumberOfStoragePtrTest_A / 2); i < kNumberOfStoragePtrTest_A; ++i){
		error_type = list_1->insertLast(TestData.storage_ptr_test_A[i], (strlen((const char*)TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertLast list_1", error_type);
	}
	printf("list_1:\n");
	list_1->print();

	printf("\t insertAt list_1\n");
	u16 position = (kNumberOfStoragePtrTest_A / 2);
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = list_1->insertAt(TestData.storage_ptr_test_B[i], (strlen((const char*)TestData.storage_ptr_test_B[i]) + 1), position);
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertAt list_1", error_type);
		position++;
	}
	printf("list_1:\n");
	list_1->print();

	printf("\t list_2 insertAt\n");
	error_type = list_2->insertAt(TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	error_type = list_2->insertAt(TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2 with NULL data", error_type);

	error_type = list_2->insertAt(TestData.single_ptr_data_2, kSingleSizeData2, 0);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	error_type = list_2->insertAt(TestData.single_ptr_data_3, kSingleSizeData3, 4);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	printf("list_2:\n");
	list_2->print();

	printf("\n\n# Test Insert\n");
	printf("\t insertLast list_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == list_3->isFull())
		{
			error_type = list_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full list (list_3 capacity = %d)\n", list_3->capacity());
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityList3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (list_3)\n");
	}
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t resize list_3\n");
	error_type = list_3->resize(10);
	TESTBASE_printFunctionResult(list_3, (u8 *)"resize list_3", error_type);
	printf("list_3:\n");
	list_3->print();

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = list_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
	}
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test Extract\n");
	printf("\t extractAt list_3\n");
	position = 2;
	TestData.storage_ptr_test_C[position] = list_3->extractAt(position);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", position);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], position);
	position++;
	TestData.storage_ptr_test_C[position] = list_3->extractAt(2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], 2);
	position++;
	TestData.storage_ptr_test_C[position] = list_3->extractAt(2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], 2);

	printf("list_3:\n");
	list_3->print();

	printf("\t extractFirst list_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = list_3->extractFirst();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at first position\n");
		else
			printf("extracted \"%s\" at first position in list_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("list_3:\n");
	list_3->print();
	printf("\t extractLast list_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = list_3->extractLast();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at Last position\n");
		else
			printf("extracted \"%s\" at last position in list_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("list_3:\n");
	list_3->print();

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == list_3->isEmpty())
		{
			data = list_3->extractLast();
			MM->free(data);
			printf("Trying to extract an element in an empty list (list_3 length = %d)\n", list_3->length());
			extract_errors++;
		}
	}
	if (extract_errors > 0)
	{
		printf("  ==> ERROR: ERROR: isEmpty doesn't work correctly (list_3)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertLast list_3\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = list_3->insertLast(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
	}
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test First\n");
	printf("\t first list_1\n");
	data = list_1->first();
	if (NULL == data)
		printf("First in list_1: NULL\n");
	else
		printf("First in list_1: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at list_3 (position %d)\n", position);
	data = list_3->at(1);
	if (NULL == data)
		printf("AT in list_3: NULL\n");
	else
		printf("AT in list_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last list_1\n");
	data = list_1->last();
	if (NULL == data)
		printf("LAST in list_1: NULL\n");
	else
		printf("LAST in list_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t list_1: [Capacity = %d] - [Length  = %d]\n", list_1->capacity(), list_1->length());
	printf("\t list_2: [Capacity = %d] - [Length  = %d]\n", list_2->capacity(), list_2->length());
	printf("\t list_3: [Capacity = %d] - [Length  = %d]\n", list_3->capacity(), list_3->length());

	printf("\n\n# Test Concat\n");
	printf("\t concat list_1 + list_3\n");
	error_type = list_1->concat(list_3);
	TESTBASE_printFunctionResult(list_1, (u8 *)"concat list_1 + list_3", error_type);
	printf("list_1:\n");
	list_1->print();
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test Length\n");
	printf("\t Length list_1 = %d \n", list_1->length());
	printf("\t Length list_2 = %d \n", list_2->length());
	printf("\t Length list_3 = %d \n", list_3->length());

	printf("\n\n# Test Reset\n");
	error_type = list_3->reset();
	TESTBASE_printFunctionResult(list_3, (u8 *)"reset list_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length list_1 = %d \n", list_1->length());
	printf("\t Length list_2 = %d \n", list_2->length());
	printf("\t Length list_3 = %d \n", list_3->length());


	printf("\n\n# Test First\n");
	printf("\t first list_3\n");
	data = list_3->first();
	if (NULL == data)
		printf("First in list_3: NULL\n");
	else
		printf("ERROR: First in list_3: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at list_3 (position %d)\n", position);
	data = list_3->at(1);
	if (NULL == data)
		printf("At in list_3: NULL\n");
	else
		printf("ERROR: AT in list_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last list_3\n");
	data = list_3->last();
	if (NULL == data)
		printf("Last in list_3: NULL\n");
	else
		printf("ERROR: Last in list_3: \"%s\"\n", data);


	printf("\n\n# Test Concat\n");
	printf("\t concat list_3 + list_2\n");
	error_type = list_3->concat(list_2);
	TESTBASE_printFunctionResult(list_3, (u8 *)"concat list_3 + list_2", error_type);
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test Destroy\n");
	printf("\t list_2 Destroy\n");
	error_type = list_2->destroy();
	list_2 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"destroy list_2", error_type);
	printf("list_2:\n");
	list_2->print();

	printf("\t list_3 Destroy\n");
	error_type = list_3->destroy();
	list_3 = NULL;
	TESTBASE_printFunctionResult(list_3, (u8 *)"destroy list_3", error_type);
	printf("list_3:\n");
	list_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t list_1 resize\n");
	error_type = list_1->resize(3);
	TESTBASE_printFunctionResult(list_1, (u8 *)"resize list_1", error_type);
	printf("list_1:\n");
	list_1->print();

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = list_2->insertFirst(data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertFirst list_2 (NOT VALID)", error_type);
	error_type = list_2->insertLast(data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertLast list_2 (NOT VALID)", error_type);
	error_type = list_2->insertAt(data, kSingleSizeBigData, 1);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2 (NOT VALID)", error_type);

	printf("\n\n# Test First\n");
	printf("\t first list_2\n");
	data = list_2->first();
	if (NULL != data)
		printf("ERROR: First in list_2 is not NULL\n");

	printf("\n\n# Test At\n");
	printf("\t at list_2 (position 1)\n");
	data = list_2->at(1);
	if (NULL != data)
		printf("ERROR: AT in list_2 is not NULL\n");

	printf("\n\n# Test Last\n");
	printf("\t last list_2\n");
	data = list_2->last();
	if (NULL != data)
		printf("ERROR: LAST in list_2 is not NULL\n");

	printf("\n\n# Test Extract\n");
	data = list_2->extractFirst();
	if (NULL != data)
	{
		printf("ERROR: trying to extractFirst from an empty list\n");
	}
	data = list_2->extractLast();
	if (NULL != data)
	{
		printf("ERROR: trying to extractLast from an empty list\n");
	}
	data = list_2->extractAt(1);
	if (NULL != data)
	{
		printf("ERROR: trying to extractAt from an empty list\n");
	}
	

	printf("\n\n# Test Concat\n");
	printf("\t concat list_1 + list_2\n");
	error_type = list_1->concat(list_2);
	TESTBASE_printFunctionResult(list_1, (u8 *)"concat list_1 + list_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = list_2->resize(5);
	TESTBASE_printFunctionResult(list_2, (u8 *)"resize list_2 (NOT VALID)", error_type);


	printf("\n\n# Test Reset\n");
	error_type = list_2->reset();
	TESTBASE_printFunctionResult(list_2, (u8 *)"reset list_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = list_2->destroy();
	TESTBASE_printFunctionResult(list_2, (u8 *)"destroy list_2 (NOT VALID)", error_type);
	error_type = list_3->destroy();
	TESTBASE_printFunctionResult(list_3, (u8 *)"destroy list_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = list_1->destroy();
	TESTBASE_printFunctionResult(list_1, (u8 *)"destroy list_1", error_type);
	error_type = ls->destroy();
	TESTBASE_printFunctionResult(ls, (u8 *)"destroy List Operations", error_type);

	printf("\nAt this point, it must be only one block of %d bytes waiting to be freed\n\n", kSingleSizeBigData);
	MM->status();
	TESTBASE_freeDataForTest();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
