// test_stack.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for stack ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_stack.h"
#include "adt_memory_node.h"
#include "adt_vector.h"
#include "EDK_MemoryManager\edk_memory_manager.h"

#include ".\..\tests\test_base.c"

const u16 kCapacityStack1 = 30;
const u16 kCapacityStack2 = 5;
const u16 kCapacityStack3 = 2;
int main()
{
	s16 error_type = 0;

	TESTBASE_generateDataForTest();

	// stack created just to have a reference to the operations
	Stack *s = NULL;
	s = STACK_create(1);
	if (NULL == s) {
		printf("\n create returned a null node in stack for ops");
		return -1;
	}
	// vectors to work with
	Stack *stack_1 = NULL;
	Stack *stack_2 = NULL;
	Stack *stack_3 = NULL;
	stack_1 = STACK_create(kCapacityStack1);
	if (NULL == stack_1) {
		printf("\n create returned a null node in stack_1\n");
		return -1;
	}
	stack_2 = STACK_create(kCapacityStack2);
	if (NULL == stack_2) {
		printf("\n create returned a null node in stack_2\n");
		return -1;
	}
	stack_3 = STACK_create(kCapacityStack3);
	if (NULL == stack_3) {
		printf("\n create returned a null node in stack_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + stack_1: %zu\n", sizeof(*stack_1));
	printf("	+ storage: %zu\n", sizeof(*(stack_1->storage_)));
	printf("  + stack_2: %zu\n", sizeof(*stack_2));
	printf("	+ storage: %zu\n", sizeof(*(stack_2->storage_)));
	printf("  + stack_3: %zu\n", sizeof(*stack_3));
	printf("	+ storage: %zu\n", sizeof(*(stack_3->storage_)));


	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = s->ops_->reset(stack_1);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"reset stack_1", error_type);

	error_type = s->ops_->push(stack_1, TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);

	error_type = s->ops_->reset(stack_1);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"reset stack_1", error_type);

	if (False == s->ops_->isEmpty(stack_1))
	{
		printf("ERROR: isEmpty doesn't work correctly (stack_1)\n");
	}

	printf("\n\n# Test Push\n");
	printf("\t push stack_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = s->ops_->push(stack_1, TestData.storage_ptr_test_A[i], (strlen(TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);
	}
	printf("stack_1:\n");
	s->ops_->print(stack_1);

	printf("\t push stack_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = s->ops_->push(stack_1, TestData.storage_ptr_test_B[i], (strlen(TestData.storage_ptr_test_B[i]) + 1));
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);
	}
	printf("stack_1:\n");
	s->ops_->print(stack_1);

	printf("\t stack_2 push\n");
	error_type = s->ops_->push(stack_2, TestData.single_ptr_data_1, kSingleSizeData1);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	error_type = s->ops_->push(stack_2, TestData.single_ptr_data_1, kSingleSizeData1);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2 with NULL data", error_type);

	error_type = s->ops_->push(stack_2, TestData.single_ptr_data_2, kSingleSizeData2);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	error_type = s->ops_->push(stack_2, TestData.single_ptr_data_3, kSingleSizeData3);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	printf("stack_2:\n");
	s->ops_->print(stack_2);

	printf("\t push stack_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == s->ops_->isFull(stack_3))
		{
			error_type = s->ops_->push(stack_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full stackvector (stack_3 capacity = %d)\n",s->ops_->capacity(stack_3));
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityStack3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (stack_3)\n");
	}
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Resize\n");
	printf("\t resize stack_3\n");
	error_type = s->ops_->resize(stack_3, 10);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"resize stack_3", error_type);
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = s->ops_->push(stack_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
	}
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Pop\n");
	printf("\t pop stack_3\n");
	u16 position = 2;
	TestData.storage_ptr_test_C[position] = s->ops_->pop(stack_3,NULL);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = s->ops_->pop(stack_3);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = s->ops_->pop(stack_3);
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);

	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\t pop stack_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = s->ops_->pop(stack_3,NULL);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at top position\n");
		else
			printf("extracted \"%s\" at top position in stack_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("stack_3:\n");
	s->ops_->print(stack_3);
	printf("\t pop stack_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = s->ops_->pop(stack_3,NULL);
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at top position\n");
		else
			printf("extracted \"%s\" at top position in stack_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == s->ops_->isEmpty(stack_3))
		{
			data = s->ops_->pop(stack_3,NULL);
			MM->free(data);
			printf("ERROR: Trying to extract an element in an empty stack (stack_3 length = %d)\n",s->ops_->length(stack_3));
			extract_errors++;
		}
	}
	if (extract_errors > 0)
	{
		printf("  ==> ERROR: isEmpty doesn't work correctly (stack_3)\n");
	}

	printf("\n\n# Test Push\n");
	printf("\t push stack_3\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = s->ops_->push(stack_3, TestData.storage_ptr_test_C[i], (strlen(TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
	}
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Top\n");
	printf("\t top stack_1\n");
	data = s->ops_->top(stack_1);
	if (NULL == data)
		printf("Top in stack_1: NULL\n");
	else
		printf("Top in stack_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t stack_1: [Capacity = %d] - [Length  = %d]\n",s->ops_->capacity(stack_1),s->ops_->length(stack_1));
	printf("\t stack_2: [Capacity = %d] - [Length  = %d]\n",s->ops_->capacity(stack_2),s->ops_->length(stack_2));
	printf("\t stack_3: [Capacity = %d] - [Length  = %d]\n",s->ops_->capacity(stack_3),s->ops_->length(stack_3));

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_1 + stack_3\n");
	error_type = s->ops_->concat(stack_1, stack_3);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"concat stack_1 + stack_3", error_type);
	printf("stack_1:\n");
	s->ops_->print(stack_1);
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Length\n");
	printf("\t Length stack_1 = %d \n",s->ops_->length(stack_1));
	printf("\t Length stack_2 = %d \n",s->ops_->length(stack_2));
	printf("\t Length stack_3 = %d \n",s->ops_->length(stack_3));

	printf("\n\n# Test Reset\n");
	error_type = s->ops_->reset(stack_3);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"reset stack_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length stack_1 = %d \n",s->ops_->length(stack_1));
	printf("\t Length stack_2 = %d \n",s->ops_->length(stack_2));
	printf("\t Length stack_3 = %d \n",s->ops_->length(stack_3));

	printf("\n\n# Test Top\n");
	printf("\t top stack_3\n");
	data = s->ops_->top(stack_3);
	if (NULL == data)
		printf("Top in stack_3: NULL\n");
	else
		printf("ERROR: First in stack_3: \"%s\"\n", data);

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_3 + stack_2\n");
	error_type = s->ops_->concat(stack_3, stack_2);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"concat stack_3 + stack_2", error_type);
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Destroy\n");
	printf("\t stack_2 Destroy\n");
	error_type = s->ops_->destroy(stack_2);
	stack_2 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"destroy stack_2", error_type);
	printf("stack_2:\n");
	s->ops_->print(stack_2);

	printf("\t stack_3 Destroy\n");
	error_type = s->ops_->destroy(stack_3);
	stack_3 = NULL;
	TESTBASE_printFunctionResult(stack_3, (u8 *)"destroy stack_3", error_type);
	printf("stack_3:\n");
	s->ops_->print(stack_3);

	printf("\n\n# Test Resize\n");
	printf("\t stack_1 resize\n");
	error_type = s->ops_->resize(stack_1, 3);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"resize stack_1", error_type);
	printf("stack_1:\n");
	s->ops_->print(stack_1);

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	printf("\n\n# Test Create\n");
	stack_2 = STACK_create(0);
	if (NULL != stack_2) {
		printf("ERROR: trying to create stack_2 with 0 capacity\n");
		return -1;
	}

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = s->ops_->push(stack_2, data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Top\n");
	printf("\t top stack_2\n");
	data = s->ops_->top(stack_2);
	if (NULL != data)
		printf("ERROR: Top in stack_2 is not NULL\n");

	printf("\n\n# Test Extract\n");
	data = s->ops_->pop(stack_2,NULL);
	if (NULL != data)
	{
		printf("ERROR: trying to pop from an empty stack\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_1 + stack_2\n");
	error_type = s->ops_->concat(stack_1, stack_2);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"concat stack_1 + stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = s->ops_->resize(stack_2, 5);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"resize stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = s->ops_->reset(&stack_2);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"reset stack_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = s->ops_->destroy(stack_2);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"destroy stack_2 (NOT VALID)", error_type);
	error_type = s->ops_->destroy(stack_3);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"destroy stack_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = s->ops_->destroy(stack_1);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"destroy stack_1", error_type);
	error_type = s->ops_->destroy(s);
	TESTBASE_printFunctionResult(s, (u8 *)"destroy Stack Operations", error_type);

	printf("\nAt this point, it must be only one block of %d bytes waiting to be freed\n\n", kSingleSizeBigData);
	MM->status();
	TESTBASE_freeDataForTest();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
