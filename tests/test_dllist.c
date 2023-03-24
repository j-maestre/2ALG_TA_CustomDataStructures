// test_list.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for list ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_dllist.h"
#include "EDK_MemoryManager/edk_memory_manager.h"

#include "./../tests/test_base.c"

const u16 kCapacityList1 = 30;
const u16 kCapacityList2 = 5;
const u16 kCapacityList3 = 2;

int main() {
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// list created just to have a reference to the operations
	DLList *ls = NULL;
	ls = LIST_create(1);
	if (NULL == ls) {
		printf("\n create returned a null node in list for ops");
		return -1;
	}
	// vectors to work with
	DLList *list_1 = NULL;
	DLList *list_2 = NULL;
	DLList *list_3 = NULL;
	list_1 = DLLIST_create(kCapacityList1);
	if (NULL == list_1) {
		printf("\n create returned a null node in list_1\n");
		return -1;
	}
	list_2 = DLLIST_create(kCapacityList2);
	if (NULL == list_2) {
		printf("\n create returned a null node in list_2\n");
		return -1;
	}
	list_3 = DLLIST_create(kCapacityList3);
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
	error_type = ls->ops_->reset(list_1);
	TESTBASE_printFunctionResult(list_1, (u8 *)"reset list_1", error_type);

	error_type = ls->ops_->insertFirst(list_1, TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(list_1, (u8 *)"insertFirst list_1", error_type);

	error_type = ls->ops_->reset(list_1);
	TESTBASE_printFunctionResult(list_1, (u8 *)"reset list_1", error_type);

	if (False == ls->ops_->isEmpty(list_1))
	{
		printf("ERROR: isEmpty doesn't work correctly (list_1)\n");
	}

	printf("\n\n# Test Insert\n");
	printf("\t insertFirst list_1\n");
	for (u16 i = 0; i < (kNumberOfStoragePtrTest_A / 2); ++i)
	{
		error_type = ls->ops_->insertFirst(list_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertFirst list_1", error_type);
	}
	printf("list_1:\n");
	ls->ops_->print(list_1);

	printf("\t insertLast list_1\n");
	for (u16 i = (kNumberOfStoragePtrTest_A / 2); i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = ls->ops_->insertLast(list_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertLast list_1", error_type);
	}
	printf("list_1:\n");
	ls->ops_->print(list_1);

	printf("\t insertAt list_1\n");
	u16 position = (kNumberOfStoragePtrTest_A / 2);
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = ls->ops_->insertAt(list_1, TestData.storage_ptr_test_B[i], (strlen(TestData.storage_ptr_test_B[i]) + 1), position);
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(list_1, (u8 *)"insertAt list_1", error_type);
		position++;
	}
	printf("list_1:\n");
	ls->ops_->print(list_1);

	printf("\t list_2 insertAt\n");
	error_type = ls->ops_->insertAt(list_2, TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	error_type = ls->ops_->insertAt(list_2, TestData.single_ptr_data_1, kSingleSizeData1, 0);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2 with NULL data", error_type);

	error_type = ls->ops_->insertAt(list_2, TestData.single_ptr_data_2, kSingleSizeData2, 0);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	error_type = ls->ops_->insertAt(list_2, TestData.single_ptr_data_3, kSingleSizeData3, 4);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2", error_type);

	printf("list_2:\n");
	ls->ops_->print(list_2);

	printf("\n\n# Test Insert\n");
	printf("\t insertLast list_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == ls->ops_->isFull(list_3))
		{
			error_type = ls->ops_->insertLast(list_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full list (list_3 capacity = %d)\n", ls->ops_->capacity(list_3));
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityList3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (list_3)\n");
	}
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test Resize\n");
	printf("\t resize list_3\n");
	error_type = ls->ops_->resize(list_3, 10);
	TESTBASE_printFunctionResult(list_3, (u8 *)"resize list_3", error_type);
	printf("list_3:\n");
	ls->ops_->print(list_3);

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = ls->ops_->insertLast(list_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
	}
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test Extract\n");
	printf("\t extractAt list_3\n");
	position = 2;
	TestData.storage_ptr_test_C[position] = ls->ops_->extractAt(list_3, position);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", position);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], position);
	position++;
	TestData.storage_ptr_test_C[position] = ls->ops_->extractAt(list_3, 2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], 2);
	position++;
	TestData.storage_ptr_test_C[position] = ls->ops_->extractAt(list_3, 2);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at position %d in list_3\n", 2);
	else
		printf("extracted \"%s\" at position %d in list_3\n", TestData.storage_ptr_test_C[position], 2);

	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\t extractFirst list_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = ls->ops_->extractFirst(list_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at first position\n");
		else
			printf("extracted \"%s\" at first position in list_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("list_3:\n");
	ls->ops_->print(list_3);
	printf("\t extractLast list_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = ls->ops_->extractLast(list_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at Last position\n");
		else
			printf("extracted \"%s\" at last position in list_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("list_3:\n");
	ls->ops_->print(list_3);

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == ls->ops_->isEmpty(list_3))
		{
			data = ls->ops_->extractLast(list_3);
			MM->free(data);
			printf("Trying to extract an element in an empty list (list_3 length = %d)\n", ls->ops_->length(list_3));
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
		error_type = ls->ops_->insertLast(list_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(list_3, (u8 *)"insertLast list_3", error_type);
	}
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test First\n");
	printf("\t first list_1\n");
	data = ls->ops_->first(list_1);
	if (NULL == data)
		printf("First in list_1: NULL\n");
	else
		printf("First in list_1: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at list_3 (position %d)\n", position);
	data = ls->ops_->at(list_3, 1);
	if (NULL == data)
		printf("AT in list_3: NULL\n");
	else
		printf("AT in list_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last list_1\n");
	data = ls->ops_->last(list_1);
	if (NULL == data)
		printf("LAST in list_1: NULL\n");
	else
		printf("LAST in list_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t list_1: [Capacity = %d] - [Length  = %d]\n", ls->ops_->capacity(list_1), ls->ops_->length(list_1));
	printf("\t list_2: [Capacity = %d] - [Length  = %d]\n", ls->ops_->capacity(list_2), ls->ops_->length(list_2));
	printf("\t list_3: [Capacity = %d] - [Length  = %d]\n", ls->ops_->capacity(list_3), ls->ops_->length(list_3));

	printf("\n\n# Test Concat\n");
	printf("\t concat list_1 + list_3\n");
	error_type = ls->ops_->concat(list_1, list_3);
	TESTBASE_printFunctionResult(list_1, (u8 *)"concat list_1 + list_3", error_type);
	printf("list_1:\n");
	ls->ops_->print(list_1);
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test Length\n");
	printf("\t Length list_1 = %d \n", ls->ops_->length(list_1));
	printf("\t Length list_2 = %d \n", ls->ops_->length(list_2));
	printf("\t Length list_3 = %d \n", ls->ops_->length(list_3));

	printf("\n\n# Test Reset\n");
	error_type = ls->ops_->reset(list_3);
	TESTBASE_printFunctionResult(list_3, (u8 *)"reset list_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length list_1 = %d \n", ls->ops_->length(list_1));
	printf("\t Length list_2 = %d \n", ls->ops_->length(list_2));
	printf("\t Length list_3 = %d \n", ls->ops_->length(list_3));


	printf("\n\n# Test First\n");
	printf("\t first list_3\n");
	data = ls->ops_->first(list_3);
	if (NULL == data)
		printf("First in list_3: NULL\n");
	else
		printf("ERROR: First in list_3: \"%s\"\n", data);

	printf("\n\n# Test At\n");
	position = 1;
	printf("\t at list_3 (position %d)\n", position);
	data = ls->ops_->at(list_3, 1);
	if (NULL == data)
		printf("At in list_3: NULL\n");
	else
		printf("ERROR: AT in list_3 (position %d): \"%s\"\n", position, data);

	printf("\n\n# Test Last\n");
	printf("\t last list_3\n");
	data = ls->ops_->last(list_3);
	if (NULL == data)
		printf("Last in list_3: NULL\n");
	else
		printf("ERROR: Last in list_3: \"%s\"\n", data);


	printf("\n\n# Test Concat\n");
	printf("\t concat list_3 + list_2\n");
	error_type = ls->ops_->concat(list_3, list_2);
	TESTBASE_printFunctionResult(list_3, (u8 *)"concat list_3 + list_2", error_type);
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test Destroy\n");
	printf("\t list_2 Destroy\n");
	error_type = ls->ops_->destroy(list_2);
	list_2 = NULL;
	TESTBASE_printFunctionResult(list_2, (u8 *)"destroy list_2", error_type);
	printf("list_2:\n");
	ls->ops_->print(list_2);

	printf("\t list_3 Destroy\n");
	error_type = ls->ops_->destroy(list_3);
	list_3 = NULL;
	TESTBASE_printFunctionResult(list_3, (u8 *)"destroy list_3", error_type);
	printf("list_3:\n");
	ls->ops_->print(list_3);

	printf("\n\n# Test Resize\n");
	printf("\t list_1 resize\n");
	error_type = ls->ops_->resize(list_1, 3);
	TESTBASE_printFunctionResult(list_1, (u8 *)"resize list_1", error_type);
	printf("list_1:\n");
	ls->ops_->print(list_1);

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = ls->ops_->insertFirst(list_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertFirst list_2 (NOT VALID)", error_type);
	error_type = ls->ops_->insertLast(list_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertLast list_2 (NOT VALID)", error_type);
	error_type = ls->ops_->insertAt(list_2, data, kSingleSizeBigData, 1);
	TESTBASE_printFunctionResult(list_2, (u8 *)"insertAt list_2 (NOT VALID)", error_type);

	printf("\n\n# Test First\n");
	printf("\t first list_2\n");
	data = ls->ops_->first(list_2);
	if (NULL != data)
		printf("ERROR: First in list_2 is not NULL\n");

	printf("\n\n# Test At\n");
	printf("\t at list_2 (position 1)\n");
	data = ls->ops_->at(list_2, 1);
	if (NULL != data)
		printf("ERROR: AT in list_2 is not NULL\n");

	printf("\n\n# Test Last\n");
	printf("\t last list_2\n");
	data = ls->ops_->last(list_2);
	if (NULL != data)
		printf("ERROR: LAST in list_2 is not NULL\n");


	printf("\n\n# Test Extract\n");
	data = ls->ops_->extractFirst(list_2);
	if (NULL != data)
	{
		printf("ERROR: trying to extractFirst from an empty list\n");
	}
	data = ls->ops_->extractLast(list_2);
	if (NULL != data)
	{
		printf("ERROR: trying to extractLast from an empty list\n");
	}
	data = ls->ops_->extractAt(list_2, 1);
	if (NULL != data)
	{
		printf("ERROR: trying to extractAt from an empty list\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat list_1 + list_2\n");
	error_type = ls->ops_->concat(list_1, list_2);
	TESTBASE_printFunctionResult(list_1, (u8 *)"concat list_1 + list_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = ls->ops_->resize(list_2, 5);
	TESTBASE_printFunctionResult(list_2, (u8 *)"resize list_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = ls->ops_->reset(list_2);
	TESTBASE_printFunctionResult(list_2, (u8 *)"reset list_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = ls->ops_->destroy(list_2);
	TESTBASE_printFunctionResult(list_2, (u8 *)"destroy list_2 (NOT VALID)", error_type);
	error_type = ls->ops_->destroy(list_3);
	TESTBASE_printFunctionResult(list_3, (u8 *)"destroy list_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = ls->ops_->destroy(list_1);
	TESTBASE_printFunctionResult(list_1, (u8 *)"destroy list_1", error_type);
	error_type = ls->ops_->destroy(ls);
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
