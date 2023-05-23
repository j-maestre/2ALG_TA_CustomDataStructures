// test_stack.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Test battery for stack ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "stack.h"
//#include "adt_memory_node.h"
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
	s = Stack::Create(1);
	if (NULL == s) {
		printf("\n create returned a null node in stack for ops");
		return -1;
	}
	// vectors to work with
	Stack *stack_1 = NULL;
	Stack *stack_2 = NULL;
	Stack *stack_3 = NULL;
	stack_1 = Stack::Create(kCapacityStack1);
	if (NULL == stack_1) {
		printf("\n create returned a null node in stack_1\n");
		return -1;
	}
	stack_2 = Stack::Create(kCapacityStack2);
	if (NULL == stack_2) {
		printf("\n create returned a null node in stack_2\n");
		return -1;
	}
	stack_3 = Stack::Create(kCapacityStack3);
	if (NULL == stack_3) {
		printf("\n create returned a null node in stack_3\n");
		return -1;
	}

	printf("Size of:\n");
	printf("  + Mem Node: %zu\n", sizeof(MemoryNode));
	printf("  + stack_1: %zu\n", sizeof(*stack_1));
	printf("	+ storage: %zu\n", sizeof(*stack_1));
	printf("  + stack_2: %zu\n", sizeof(*stack_2));
	printf("	+ storage: %zu\n", sizeof(*stack_2));
	printf("  + stack_3: %zu\n", sizeof(*stack_3));
	printf("	+ storage: %zu\n", sizeof(*stack_3));


	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// reset
	printf("\n\n# Test Reset\n");
	error_type = stack_1->reset();
	TESTBASE_printFunctionResult(stack_1, (u8 *)"reset stack_1", error_type);

	error_type = stack_1->push(TestData.single_ptr_data_4, kSingleSizeData4);
	TestData.single_ptr_data_4 = NULL;
	TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);

	error_type = stack_1->reset();
	TESTBASE_printFunctionResult(stack_1, (u8 *)"reset stack_1", error_type);

	if (False == stack_1->isEmpty())
	{
		printf("ERROR: isEmpty doesn't work correctly (stack_1)\n");
	}

	printf("\n\n# Test Push\n");
	printf("\t push stack_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_A; ++i)
	{
		error_type = stack_1->push(TestData.storage_ptr_test_A[i], (strlen((const char*)TestData.storage_ptr_test_A[i]) + 1));
		TestData.storage_ptr_test_A[i] = NULL;
		TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);
	}
	printf("stack_1:\n");
	stack_1->print();

	printf("\t push stack_1\n");
	for (u16 i = 0; i < kNumberOfStoragePtrTest_B; ++i)
	{
		error_type = stack_1->push(TestData.storage_ptr_test_B[i], (strlen((const char*)TestData.storage_ptr_test_B[i]) + 1));
		TestData.storage_ptr_test_B[i] = NULL;
		TESTBASE_printFunctionResult(stack_1, (u8 *)"push stack_1", error_type);
	}
	printf("stack_1:\n");
	stack_1->print();

	printf("\t stack_2 push\n");
	error_type = stack_2->push(TestData.single_ptr_data_1, kSingleSizeData1);
	TestData.single_ptr_data_1 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	error_type = stack_2->push( TestData.single_ptr_data_1, kSingleSizeData1);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2 with NULL data", error_type);

	error_type = stack_2->push( TestData.single_ptr_data_2, kSingleSizeData2);
	TestData.single_ptr_data_2 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	error_type = stack_2->push( TestData.single_ptr_data_3, kSingleSizeData3);
	TestData.single_ptr_data_3 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2", error_type);

	printf("stack_2:\n");
	stack_2->print();

	printf("\t push stack_3\n");
	u16 insert_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == stack_3->isFull())
		{
			error_type = stack_3->push(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
			TestData.storage_ptr_test_C[i] = NULL;
			TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
		}
		else
		{
			printf("ERROR: Trying to insert an element in a full stackvector (stack_3 capacity = %d)\n",stack_3->capacity());
			insert_errors++;
		}
	}
	if ((kNumberOfStoragePtrTest_C - kCapacityStack3) != insert_errors)
	{
		printf("  ==> ERROR: isFull doesn't work correctly (stack_3)\n");
	}
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t resize stack_3\n");
	error_type = stack_3->resize(10);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"resize stack_3", error_type);
	printf("stack_3:\n");
	stack_3->print();

	for (u16 i = 2; i < kNumberOfStoragePtrTest_C; ++i)
	{
		error_type = stack_3->push(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
	}
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Pop\n");
	printf("\t pop stack_3\n");
	u16 position = 2;
	TestData.storage_ptr_test_C[position] = stack_3->pop();
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = stack_3->pop();
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);
	position++;
	TestData.storage_ptr_test_C[position] = stack_3->pop();
	if (NULL == TestData.storage_ptr_test_C[position])
		printf("ERROR: NULL pointer extracted at top stack_3\n");
	else
		printf("extracted \"%s\" at top in stack_3\n", TestData.storage_ptr_test_C[position]);

	printf("stack_3:\n");
	stack_3->print();

	printf("\t pop stack_3\n");
	for (u16 i = 0; i < 2; ++i)
	{
		TestData.storage_ptr_test_C[i] = stack_3->pop();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at top position\n");
		else
			printf("extracted \"%s\" at top position in stack_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("stack_3:\n");
	stack_3->print();
	printf("\t pop stack_3\n");
	for (u16 i = 6; i > 4; --i)
	{
		TestData.storage_ptr_test_C[i] = stack_3->pop();
		if (NULL == TestData.storage_ptr_test_C[i])
			printf("ERROR: NULL pointer extracted at top position\n");
		else
			printf("extracted \"%s\" at top position in stack_3\n", TestData.storage_ptr_test_C[i]);
	}
	printf("stack_3:\n");
	stack_3->print();

	void *data = NULL;
	u16 extract_errors = 0;
	for (u16 i = 0; i < kNumberOfStoragePtrTest_C; ++i)
	{
		if (False == stack_3->isEmpty())
		{
			data = stack_3->pop();
			MM->free(data);
			printf("ERROR: Trying to extract an element in an empty stack (stack_3 length = %d)\n",stack_3->length());
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
		error_type = stack_3->push(TestData.storage_ptr_test_C[i], (strlen((const char*)TestData.storage_ptr_test_C[i]) + 1));
		TestData.storage_ptr_test_C[i] = NULL;
		TESTBASE_printFunctionResult(stack_3, (u8 *)"push stack_3", error_type);
	}
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Top\n");
	printf("\t top stack_1\n");
	data = stack_1->top();
	if (NULL == data)
		printf("Top in stack_1: NULL\n");
	else
		printf("Top in stack_1: \"%s\"\n", data);

	printf("\n\n# Test Length\n");
	printf("\t stack_1: [Capacity = %d] - [Length  = %d]\n",stack_1->capacity(),stack_1->length());
	printf("\t stack_2: [Capacity = %d] - [Length  = %d]\n",stack_2->capacity(),stack_2->length());
	printf("\t stack_3: [Capacity = %d] - [Length  = %d]\n",stack_3->capacity(),stack_3->length());

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_1 + stack_3\n");
	error_type = stack_1->concat(stack_3);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"concat stack_1 + stack_3", error_type);
	printf("stack_1:\n");
	stack_1->print();
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Length\n");
	printf("\t Length stack_1 = %d \n",stack_1->length());
	printf("\t Length stack_2 = %d \n",stack_2->length());
	printf("\t Length stack_3 = %d \n",stack_3->length());

	printf("\n\n# Test Reset\n");
	error_type = stack_3->reset();
	TESTBASE_printFunctionResult(stack_3, (u8 *)"reset stack_3", error_type);

	printf("\n\n# Test Length\n");
	printf("\t Length stack_1 = %d \n",stack_1->length());
	printf("\t Length stack_2 = %d \n",stack_2->length());
	printf("\t Length stack_3 = %d \n",stack_3->length());

	printf("\n\n# Test Top\n");
	printf("\t top stack_3\n");
	data = stack_3->top();
	if (NULL == data)
		printf("Top in stack_3: NULL\n");
	else
		printf("ERROR: First in stack_3: \"%s\"\n", data);

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_3 + stack_2\n");
	error_type = stack_3->concat(stack_2);
	TESTBASE_printFunctionResult(stack_3, (u8 *)"concat stack_3 + stack_2", error_type);
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Destroy\n");
	printf("\t stack_2 Destroy\n");
	error_type = stack_2->destroy();
	stack_2 = NULL;
	TESTBASE_printFunctionResult(stack_2, (u8 *)"destroy stack_2", error_type);
	printf("stack_2:\n");
	stack_2->print();

	printf("\t stack_3 Destroy\n");
	error_type = stack_3->destroy();
	stack_3 = NULL;
	TESTBASE_printFunctionResult(stack_3, (u8 *)"destroy stack_3", error_type);
	printf("stack_3:\n");
	stack_3->print();

	printf("\n\n# Test Resize\n");
	printf("\t stack_1 resize\n");
	error_type = stack_1->resize(3);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"resize stack_1", error_type);
	printf("stack_1:\n");
	stack_1->print();

	MM->status();

	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	printf("\n\n# Test Create\n");
	stack_2 = Stack::Create(0);
	if (NULL != stack_2) {
		printf("ERROR: trying to create stack_2 with 0 capacity\n");
		return -1;
	}

	printf("\n\n# Test Insert\n");
	data = TestData.single_ptr_big_data;
	error_type = stack_2->push(data, kSingleSizeBigData);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"push stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Top\n");
	printf("\t top stack_2\n");
	data = stack_2->top();
	if (NULL != data)
		printf("ERROR: Top in stack_2 is not NULL\n");

	printf("\n\n# Test Extract\n");
	data = stack_2->pop();
	if (NULL != data)
	{
		printf("ERROR: trying to pop from an empty stack\n");
	}

	printf("\n\n# Test Concat\n");
	printf("\t concat stack_1 + stack_2\n");
	error_type = stack_1->concat(stack_2);
	TESTBASE_printFunctionResult(stack_1, (u8 *)"concat stack_1 + stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Resize\n");
	error_type = stack_2->resize(5);
	TESTBASE_printFunctionResult(stack_2, (u8 *)"resize stack_2 (NOT VALID)", error_type);

	printf("\n\n# Test Reset\n");
	error_type = stack_2->reset();
	TESTBASE_printFunctionResult(stack_2, (u8 *)"reset stack_2 (NOT VALID)", error_type);


	printf("\n\n# Test Destroy\n");
	error_type = stack_2->destroy();
	TESTBASE_printFunctionResult(stack_2, (u8 *)"destroy stack_2 (NOT VALID)", error_type);
	error_type = stack_3->destroy();
	TESTBASE_printFunctionResult(stack_3, (u8 *)"destroy stack_3 (NOT VALID)", error_type);


	// Work is done, clean the system
	error_type = stack_1->destroy();
	TESTBASE_printFunctionResult(stack_1, (u8 *)"destroy stack_1", error_type);
	error_type = s->destroy();
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
