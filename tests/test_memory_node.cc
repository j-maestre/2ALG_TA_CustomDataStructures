// test_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
//Test battery for memory_node

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_node.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "EDK_MemoryManager/edk_memory_manager.h"

#ifdef __cplusplus
}
#endif //__cplusplus

char *error_codes[] = {{"OK"},{"NULL"},{"Memory error"},{"node is NULL"},{"node->data_ is NULL"},{"bytes is ZERO"},{"No memory when malloc"},{"Vector is NULL"},{"Storage NULL"},{"Size is ZERO"},{"Vector tail exceeds capacity"},{"Vecot position exceeds capacity"},{"Vector position exceeds tail"},{"Vector is FULL"},{"Callback is NULL"}};

void printFunctionResult(MemoryNode *mn, u8 *msg, s16 error_type) {
	u8 *error_msg = (u8 *)MM->malloc (sizeof(u8) * 100);
	if (NULL == error_msg)
	{
		printf(" [TEST] Error allocating error mesage\n");
		return;
	}
	printf(" [TEST] Function %s returns ", msg);
  switch (error_type) { //Should this switch be improved by an "Error Msg" depending on the "Error Code"?
    case 0:
		  printf("OK");
		  break;
	  default:
		  strcpy((char *) error_msg, "");
		  printf("FAIL with error %d (%s)", error_type,error_codes[error_type*-1]);
		  break;
	}
	printf(" in address = %p", mn);
	printf("\n");
	MM->free(error_msg);
}
s16 printMemoryNodeInfo(MemoryNode *node) {
	printf("\n [TEST] Node Info:\n");
	if (NULL == node)
	{
		printf(" [TEST] Node = NULL \n");
		return -1;
	}
	if (NULL == node->data())
	{
		printf(" [TEST] Data = NULL\n");
		printf(" [TEST] Node size:%zu\n", node->size());
		return -1;
	}
	if (0 == node->size())
	{
		printf(" [TEST] Size = 0\n");
		return -1;
	}
	printf(" [TEST] Node address = %p\n", node);
	printf(" [TEST] Data address = %p\n", node->data());
	printf(" [TEST] Node size:%zu\n", node->size());
	return 1;
}
void printMemoryNodeInfoAsChar(MemoryNode *node) {
	if (-1 == printMemoryNodeInfo(node))
	{
		return;
	}
	printf(" [TEST] Data = ");
	u8* ptr_iterator = (u8*)node->data();
	for (u16 i = 0; i < node->size(); ++i)
	{
		printf("%c", *(ptr_iterator++));
	}
	printf("\n");
}
void printMemoryNodeInfoAsString(MemoryNode *node) {
	if (-1 == printMemoryNodeInfo(node))
	{
		return;
	}
	printf(" [TEST] Data = ");
	printf("%s", (u8*)node->data());
	printf("\n");
}
void printMemoryNodeInfoAsHex(MemoryNode *node) {
	if (-1 == printMemoryNodeInfo(node))
	{
		return;
	}
	printf(" [TEST] Data = ");
	u8* ptr_iterator = (u8*)node->data();
	for (u16 i = 0; i < node->size(); ++i)
	{
		printf("%X ", *(ptr_iterator++));
	}
	printf("\n");
}

u8 *big_data_msg = (u8 *)"\n   ABGS - Artificial Bytes Game Studio\n  **  Tap Pop Balloon - Combo Party  **\n      Available for Android and iOS\n\n";
#define kIterationsBigData 10

const u16 kSizeData1 = (sizeof(u8) * 5);
const u16 kSizeData2 = (sizeof(u8) * 15);
const u16 kSizeData3 = (sizeof(u8) * 10);
const u16 kSizeData4 = (sizeof(u8) * 117);
const u16 kSizeBigData = (sizeof(u8) * (117 * kIterationsBigData));

int main()
{
	//printf("big_data_msg size = %d", strlen((char *)big_data_msg));
	s16 error_type;
	u8 *ptr_data_1 = (u8*)MM->malloc(sizeof(u8) * kSizeData1); // abcde
	if (NULL == ptr_data_1) {
		printf("\n create returned a null node in ptr_data_1");
		return -1;
	}
	u8 *ptr_data_2 = (u8*)MM->malloc(sizeof(u8) * kSizeData2); // fghijklmnopqrst
	if (NULL == ptr_data_2) {
		printf("\n create returned a null node in ptr_data_2");
		return -1;
	}
	u8 *ptr_data_3 = (u8*)MM->malloc(sizeof(u8) * kSizeData3); // 0123456789
	if (NULL == ptr_data_3) {
		printf("\n create returned a null node in ptr_data_3");
		return -1;
	}
	u8 *ptr_data_4 = (u8*)MM->malloc(sizeof(u8) * kSizeData4); // ABGS
	if (NULL == ptr_data_4) {
		printf("\n create returned a null node in ptr_data_4");
		return -1;
	}
	u8 *ptr_big_data = (u8*)MM->malloc(sizeof(u8) * kSizeBigData);
	if (NULL == ptr_big_data) {
		printf("\n create returned a null node in ptr_big_data");
		return -1;
	}
	for (u8 i = 0; i < kSizeData1; ++i)
	{
		*(ptr_data_1 + i) = 'a' + i;
	}
	for (u8 i = 0; i < kSizeData2; ++i)
	{
		*(ptr_data_2 + i) = 'f' + i;
	}
	for (u8 i = 0; i < kSizeData3; ++i)
	{
		*(ptr_data_3 + i) = '0' + i;
	}
	for (u8 i = 0; i < kSizeData4; ++i)
	{
		*(ptr_data_4 + i) = '0' + i;
	}
	strncpy((char *)ptr_data_4, (char *)big_data_msg, kSizeData4);

	printf("\n");
	printf("ptr_data_1 = ");
	for (u8 i = 0; i < kSizeData1; ++i)
	{
		printf("%c", *(ptr_data_1 + i));
	}
	printf("\n");
	printf("ptr_data_2 = ");
	for (u8 i = 0; i < kSizeData2; ++i)
	{
		printf("%c", *(ptr_data_2 + i));
	}
	printf("\n");
	printf("ptr_data_3 = ");
	for (u8 i = 0; i < kSizeData3; ++i)
	{
		printf("%c", *(ptr_data_3 + i));
	}
	printf("\n");
	printf("ptr_data_4 = ");
	for (u8 i = 0; i < kSizeData4; ++i)
	{
		printf("%c", *(ptr_data_4 + i));
	}
	printf("\n");
	// node created just to have a reference to the operations
	MemoryNode *mn = NULL;
	// nodes to work with
	MemoryNode *node_1 = NULL;
	MemoryNode *node_2 = NULL;
	MemoryNode *node_3 = NULL;

	node_1 = MemoryNode::Create();
	if (NULL == node_1) {
		printf("\n create returned a null node in node_1");
		return -1;
	}
	node_2 = MemoryNode::Create();
	if (NULL == node_2) {
		printf("\n create returned a null node in node_2");
		return -1;
	}
	error_type = MemoryNode::CreateFromRef(&node_3);
	printFunctionResult(node_3, (u8 *)"createFromRef Node 3", error_type);

	// node created just to have a reference to the operations
	mn = MemoryNode::Create();
	if (NULL == mn) {
		printf("\n create returned a null node in node for ops");
		return -1;
	}
	//FIRST BATTERY
	printf("---------------- FIRST BATTERY ----------------\n\n");
	// setData
	printf("\n\n# Test setData\n");
	printf("\t setData Node 1\n");
	error_type = mn->setData(ptr_data_1, kSizeData1);
	printFunctionResult(node_1, (u8 *)"setData Node 1", error_type);
	printf("Node 1:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_1);

	printf("\t setData Node 2\n");
	error_type = mn->setData(ptr_data_3, kSizeData3);
	printFunctionResult(node_2, (u8 *)"setData Node 2", error_type);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);

	// memSet
	printf("\n\n# Test memSet in Node 2 to '.'\n");
	error_type = mn->memSet(0x2E);
	printFunctionResult(node_2, (u8 *)"memSet", error_type);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);

	// reset
	printf("\n# Test reset Node 2\n");
	error_type = mn->reset();
	printFunctionResult(node_2, (u8 *)"reset", error_type);
	printf("Node 2:\n");
	mn->print();

	// setData
	printf("\n# setData Node 2\n");
	error_type = mn->setData(ptr_data_2, kSizeData2);
	printFunctionResult(node_2, (u8 *)"setData", error_type);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);

	// memCopy
	printf("\n\n# Test memCopy Node 2 to Node 2\n");
	error_type = mn->memCopy(mn->data(), mn->size());
	printFunctionResult(node_2, (u8 *)"memCopy", error_type);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);

	// memConcat
	printf("\n\n# Test memConcat Node 1 and Node 2\n\nBefore:\n");
	printf("Node 1:\n");
	mn->print();
	printf("Node 2:\n");
	mn->print();
	printf("\n");
	error_type = mn->memConcat(mn->data(), mn->size());
	printFunctionResult(node_1, (u8 *)"memConcat Node 1 and Node 2", error_type);
	printf("After:\n");
	printf("Node 1:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_1);
	printf("Node 2:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_2);

	// memMask
	printf("\n\n# Test memMask in Node 1 (mask to Capitals)\n");
	error_type = mn->memMask(0x5F);
	printFunctionResult(node_1, (u8 *)"memMask", error_type);
	printf("Node 1:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_1);

	// free
	printf("\n# Test Free Node 2\n");
	error_type = mn->free();
	printFunctionResult(node_2, (u8 *)"free", error_type);

	// setData
	printf("\n# setData Node 3 (sharing with Node 1)\n");
	error_type = mn->setData(mn->data(), mn->size());
	printFunctionResult(node_3, (u8 *)"setData", error_type);
	printf("Node 3:\n");
	mn->print();
	printMemoryNodeInfoAsChar(node_3);

	// softFree
	printf("\n# softFree Node 1 (shared with Node 3)\n");
	error_type = mn->softFree();
	printFunctionResult(node_1, (u8 *)"softFree", error_type);
	printf("Node 3:\n");
	mn->print();

	// free
	printf("\n# Test Free\n");
	error_type = mn->free();
	printFunctionResult(node_3, (u8 *)"free Node 3", error_type);


/*
	// NULL COMPROBATION
	printf("\n\n---------------- NULL BATTERY ----------------\n\n");
	node_1 = MemoryNode::Create();
	if (NULL == node_1) {
		printf("\n create returned a null node in node_1");
		return -1;
	}
	error_type = MemoryNode::CreateFromRef(NULL);
	printFunctionResult(node_1, (u8 *)"createFromRef(NULL)", error_type);
	error_type = mn->setData(node_1, NULL, 4);
	printFunctionResult(node_1, (u8 *)"setData(node_1, NULL, 4)", error_type);
	error_type = mn->setData(NULL, ptr_data_1, 4);
	printFunctionResult(node_1, (u8 *)"setData(NULL, ptr_data_1, 4)", error_type);
	error_type = mn->size(NULL);
	printFunctionResult(node_1, (u8 *)"size(NULL)", error_type);
	error_type = mn->reset(NULL);
	printFunctionResult(node_1, (u8 *)"reset(NULL)", error_type);
	error_type = mn->free(NULL);
	printFunctionResult(node_1, (u8 *)"free(NULL)", error_type);
	error_type = mn->softFree(NULL);
	printFunctionResult(node_1, (u8 *)"softFree(NULL)", error_type);
	error_type = mn->memSet(NULL, 'l');
	printFunctionResult(node_1, (u8 *)"memSet(NULL, 'l')", error_type);
	error_type = mn->memCopy(NULL, ptr_data_1, 4);
	printFunctionResult(node_1, (u8 *)"memCopy(NULL, ptr_data_1, 4)", error_type);
	error_type = mn->memCopy(node_1, NULL, 4);
	printFunctionResult(node_1, (u8 *)"memCopy(node_1, NULL, 4)", error_type);
	error_type = mn->memCopy(node_1, (void *)ptr_data_1, 0);
	printFunctionResult(node_1, (u8 *)"memCopy(node_1, ptr_data_1, NULL)", error_type);
	error_type = mn->memConcat(NULL, (void *)ptr_data_1, 4);
	printFunctionResult(node_1, (u8 *)"memConcat(NULL, ptr_data_1, 4)", error_type);
	error_type = mn->memConcat(node_1, NULL, 4);
	printFunctionResult(node_1, (u8 *)"memConcat(node_1, NULL, 4)", error_type);
	error_type = mn->memMask(NULL, 7);
	printFunctionResult(node_1, (u8 *)"memMask(NULL, 7)", error_type);
	mn->print(NULL);

	//BIG DATA BATTERY
	printf("\n\n---------------- Big Data BATTERY ----------------\n\n");
	error_type = mn->reset(node_1);
	printFunctionResult(node_1, (u8 *)"reset node 1", error_type);
	node_2 = MEMNODE_create();
	if (NULL == node_2) {
		printf("\n create returned a null node in node_2");
		return -1;
	}
	node_3 = MEMNODE_create();
	if (NULL == node_3) {
		printf("\n create returned a null node in node_3");
		return -1;
	}
	error_type = mn->setData(node_3, ptr_data_4, kSizeData4);
	printFunctionResult(node_1, (u8 *)"setData Node 3", error_type);
	mn->print(node_3);
	printMemoryNodeInfoAsChar(node_3);

	for (int i = 0; i < kIterationsBigData; ++i)
	{
		printf("---------------------------------------------------------\n");
		printf("Big data iteration %d\n", i);
		error_type = node_2->memCopy(node_2, mn->data(node_3), mn->size(node_3));
		printFunctionResult(node_2, (u8 *)"memCopy from Node 3 to Node 2", error_type);

		error_type = mn->memConcat(node_1, mn->data(node_2), mn->size(node_2));
		printFunctionResult(node_1, (u8 *)"memConcat Node 1 and Node 2", error_type);

		error_type = mn->reset(node_2);
		printFunctionResult(node_2, (u8 *)"reset node 2", error_type);
	}
	printf("---------------------------------------------------------\n");
	printf("Final Result with Big data\n");
	printf("Node 1\n");
	printMemoryNodeInfoAsChar(node_1);
	printf("Node 2\n");
	printMemoryNodeInfoAsChar(node_2);
	//END BIG DATA

	// free
	printf("\n# Test Free\n");
	error_type = mn->free(node_1);
	printFunctionResult(node_1, (u8 *)"free Node 1", error_type);
	error_type = mn->free(node_2);
	printFunctionResult(node_2, (u8 *)"free Node 2", error_type);
	error_type = mn->free(node_3);
	printFunctionResult(node_3, (u8 *)"free Node 3", error_type);
	error_type = mn->free(mn);
  MM->free(ptr_big_data);
*/
  MM->status();
  MM->destroy();

	printf("Press ENTER to continue\n");
	getchar();
	return 0;
}
