// test_queue.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for queue ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_queue.h"
#include "adt_memory_node.h"
#include "adt_list.h"
#include "EDK_MemoryManager\edk_memory_manager.h"

#include ".\..\tests\test_base.c"

const u16 kCapacityQueue1 = 30;
const u16 kCapacityQueue2 = 5;
const u16 kCapacityQueue3 = 2;
int main()
{
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// vector created just to have a reference to the operations
	Queue *q = NULL;
	q = QUEUE_create(1);
	if (NULL == q) {
		printf("\n create returned a null node in vector for ops");
		return -1;
	}
	// vectors to work with
	Queue *queue_1 = NULL;
	Queue *queue_2 = NULL;
	Queue *queue_3 = NULL;
	queue_1 = QUEUE_create(kCapacityQueue1);
	if (NULL == queue_1) {
		printf("\n create returned a null node in queue_1\n");
		return -1;
	}
	queue_2 = QUEUE_create(kCapacityQueue2);
	if (NULL == queue_2) {
		printf("\n create returned a null node in queue_2\n");
		return -1;
	}
	queue_3 = QUEUE_create(kCapacityQueue3);
	if (NULL == queue_3) {
		printf("\n create returned a null node in queue_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + queue_1: %zu\n", sizeof(*queue_1));
	printf("  + queue_2: %zu\n", sizeof(*queue_2));
	printf("  + queue_3: %zu\n", sizeof(*queue_3));


	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = q->ops_->reset(queue_1);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"reset queue_1", error_type);

	error_type = q->ops_->enqueue(queue_1, TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(queue_1, (u8 *)"enqueue queue_1", error_type);

	error_type = q->ops_->reset(queue_1);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"reset queue_1", error_type);

	if (False == q->ops_->isEmpty(queue_1))
	{
		printf("ERROR: isEmpty doesn't work correctly (queue_1)\n");
	}

	printf("\n\n# Test Enqueue\n");
	printf("\t enqueue queue_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = q->ops_->enqueue(queue_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(queue_1, (u8 *)"enqueue queue_1", error_type);
	}
	printf("queue_1:\n");
	q->ops_->print(queue_1);

	printf("\t enqueue queue_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = q->ops_->enqueue(queue_1, TestData.storage_ptr_test_B[i], (strlen(TestData.storage_ptr_test_B[i]) + 1));
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(queue_1, (u8 *)"enqueue queue_1", error_type);
	}
	printf("queue_1:\n");
	q->ops_->print(queue_1);

	printf("\t queue_2 enqueue\n");
	error_type = q->ops_->enqueue(queue_2, TestData.single_ptr_data_1, kSingleSizeData1);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(queue_2, (u8 *)"enqueue queue_2", error_type);

	error_type = q->ops_->enqueue(queue_2, TestData.single_ptr_data_1, kSingleSizeData1);
	TESTBASE_printFunctionResult(queue_2, (u8 *)"enqueue queue_2 with NULL data", error_type);

	error_type = q->ops_->enqueue(queue_2, TestData.single_ptr_data_2, kSingleSizeData2);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(queue_2, (u8 *)"enqueue queue_2", error_type);

	error_type = q->ops_->enqueue(queue_2, TestData.single_ptr_data_3, kSingleSizeData3);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(queue_2, (u8 *)"enqueue queue_2", error_type);

	printf("queue_2:\n");
	q->ops_->print(queue_2);

	printf("\t enqueue queue_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == q->ops_->isFull(queue_3))
		{
			error_type = q->ops_->enqueue(queue_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(queue_3, (u8 *)"enqueue queue_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full vector (queue_3 capacity = %d)\n",q->ops_->capacity(queue_3));
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityQueue3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (queue_3)\n");
	}
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Resize\n");
	printf("\t resize queue_3\n");
	error_type = q->ops_->resize(queue_3, 10);
	TESTBASE_printFunctionResult(queue_3, (u8 *)"resize queue_3", error_type);
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = q->ops_->enqueue(queue_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(queue_3, (u8 *)"enqueue queue_3", error_type);
	}
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Pop\n");
	printf("\t dequeue queue_3\n");
	u16 position = 2;
	TestData.storage_ptr_test_C[position] = q->ops_->dequeue(queue_3);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at front queue_3\n");
	else
		printf("extracted \"%s\" at front in queue_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = q->ops_->dequeue(queue_3);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at front queue_3\n");
	else
		printf("extracted \"%s\" at front in queue_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = q->ops_->dequeue(queue_3);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at front queue_3\n");
	else
		printf("extracted \"%s\" at front in queue_3\n", TestData.storage_ptr_test_C[position]);

	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\t dequeue queue_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = q->ops_->dequeue(queue_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at front position\n");
		else
			printf("extracted \"%s\" at front position in queue_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("queue_3:\n");
	q->ops_->print(queue_3);
	printf("\t dequeue queue_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = q->ops_->dequeue(queue_3);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at front position\n");
		else
			printf("extracted \"%s\" at front position in queue_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == q->ops_->isEmpty(queue_3))
		{
			data = q->ops_->dequeue(queue_3);
			MM->free(data);
			printf("ERROR: Trying to extract an element in an empty stack (queue_3 length = %d)\n",q->ops_->length(queue_3));
			extract_errors++;
		}
	}
	if (extract_errors > 0)
	{
		printf("  ==> ERROR: isEmpty doesn't work correctly (queue_3)\n");
	}

	printf("\n\n# Test Push\n");
	printf("\t enqueue queue_3\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = q->ops_->enqueue(queue_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(queue_3, (u8 *)"enqueue queue_3", error_type);
	}
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Front\n");
	printf("\t front queue_1\n");
	data = q->ops_->front(queue_1);
	if (NULL == data)
		printf("Front in queue_1: NULL\n");
	else
		printf("Front in queue_1: \"%s\"\n", data);

	printf("\n\n# Test Back\n");
	printf("\t back queue_1\n");
	data = q->ops_->back(queue_1);
	if (NULL == data)
		printf("Back in queue_1: NULL\n");
	else
		printf("Back in queue_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t queue_1: [Capacity = %d] - [Length  = %d]\n",q->ops_->capacity(queue_1),q->ops_->length(queue_1));
	printf("\t queue_2: [Capacity = %d] - [Length  = %d]\n",q->ops_->capacity(queue_2),q->ops_->length(queue_2));
	printf("\t queue_3: [Capacity = %d] - [Length  = %d]\n",q->ops_->capacity(queue_3),q->ops_->length(queue_3));

	printf("\n\n# Test Concat\n");
	printf("\t concat queue_1 + queue_3\n");
	error_type = q->ops_->concat(queue_1, queue_3);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"concat queue_1 + queue_3", error_type);
	printf("queue_1:\n");
	q->ops_->print(queue_1);
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Length\n");
	printf("\t Length queue_1 = %d \n",q->ops_->length(queue_1));
	printf("\t Length queue_2 = %d \n",q->ops_->length(queue_2));
	printf("\t Length queue_3 = %d \n",q->ops_->length(queue_3));

	printf("\n\n# Test Reset\n");
	error_type = q->ops_->reset(queue_3);
	TESTBASE_printFunctionResult(queue_3, (u8 *)"reset queue_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length queue_1 = %d \n",q->ops_->length(queue_1));
	printf("\t Length queue_2 = %d \n",q->ops_->length(queue_2));
	printf("\t Length queue_3 = %d \n",q->ops_->length(queue_3));

	printf("\n\n# Test Front\n");
	printf("\t front queue_3\n");
	data = q->ops_->front(queue_3);
	if (NULL == data)
		printf("Front in queue_3: NULL\n");
	else
		printf("ERROR: Front in queue_3: \"%s\"\n", data);

	printf("\n\n# Test Back\n");
	printf("\t back queue_3\n");
	data = q->ops_->back(queue_3);
	if (NULL == data)
		printf("Back in queue_3: NULL\n");
	else
		printf("Back in queue_3: \"%s\"\n", data);

	printf("\n\n# Test Concat\n");
	printf("\t concat queue_3 + queue_2\n");
	error_type = q->ops_->concat(queue_3, queue_2);
	TESTBASE_printFunctionResult(queue_3, (u8 *)"concat queue_3 + queue_2", error_type);
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Destroy\n");
	printf("\t queue_2 Destroy\n");
	error_type = q->ops_->destroy(queue_2);
	queue_2 = NULL;
	TESTBASE_printFunctionResult(queue_2, (u8 *)"destroy queue_2", error_type);
	printf("queue_2:\n");
	q->ops_->print(queue_2);

	printf("\t queue_3 Destroy\n");
	error_type = q->ops_->destroy(queue_3);
	queue_3 = NULL;
	TESTBASE_printFunctionResult(queue_3, (u8 *)"destroy queue_3", error_type);
	printf("queue_3:\n");
	q->ops_->print(queue_3);

	printf("\n\n# Test Resize\n");
	printf("\t queue_1 resize\n");
	error_type = q->ops_->resize(queue_1, 3);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"resize queue_1", error_type);
	printf("queue_1:\n");
	q->ops_->print(queue_1);

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = q->ops_->enqueue(queue_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(queue_2, (u8 *)"enqueue queue_2 (NOT VALID)", error_type);

	printf("\n\n# Test Front\n");
	printf("\t front queue_2\n");
	data = q->ops_->front(queue_2);
	if (NULL != data)
		printf("ERROR: Front in queue_2 is not NULL\n");

	printf("\n\n# Test Back\n");
	printf("\t back queue_2\n");
	data = q->ops_->back(queue_2);
	if (NULL == data)
		printf("Back in queue_2: NULL\n");
	else
		printf("Back in queue_2: \"%s\"\n", data);

	printf("\n\n# Test Extract\n");
	data = q->ops_->dequeue(queue_2);
	if (NULL != data)
	{
		printf("ERROR: trying to dequeue from an empty stack\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat queue_1 + queue_2\n");
	error_type = q->ops_->concat(queue_1, queue_2);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"concat queue_1 + queue_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = q->ops_->resize(queue_2, 5);
	TESTBASE_printFunctionResult(queue_2, (u8 *)"resize queue_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = q->ops_->reset(&queue_2);
	TESTBASE_printFunctionResult(queue_2, (u8 *)"reset queue_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = q->ops_->destroy(queue_2);
	TESTBASE_printFunctionResult(queue_2, (u8 *)"destroy queue_2 (NOT VALID)", error_type);
	error_type = q->ops_->destroy(queue_3);
	TESTBASE_printFunctionResult(queue_3, (u8 *)"destroy queue_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = q->ops_->destroy(queue_1);
	TESTBASE_printFunctionResult(queue_1, (u8 *)"destroy queue_1", error_type);
	error_type = q->ops_->destroy(q);
	TESTBASE_printFunctionResult(q, (u8 *)"destroy Queue Operations", error_type);

	printf("\nAt this point, it must be only one block of %d bytes waiting to be freed\n\n", kSingleSizeBigData);
	MM->status();
	TESTBASE_freeDataForTest();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
