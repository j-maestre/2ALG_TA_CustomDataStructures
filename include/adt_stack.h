/**
 * @file adt_memory_node.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

typedef struct adt_stack_s {
	struct adt_vector_s *storage_;
	struct stack_ops_s *ops_;
} Stack;

struct stack_ops_s
{
	s16 (*reset)(Stack *stack);
	s16 (*push)(Stack *stack, void *data, u16 bytes);
	boolean (*isEmpty)(Stack *stack);
	boolean (*isFull)(Stack *stack);
	u16 (*capacity)(Stack *stack);
	u16 (*length)(Stack *stack);
	void* (*top)(Stack *stack);
	s16 (*concat)(Stack *stack, Stack *stack_src);
	s16 (*resize)(Stack *stack, u16 new_capacity);
	s16 (*destroy)(Stack *stack);
	void* (*pop)(Stack *stack);
	void (*print)(Stack *stack);
};

Stack* STACK_create(u16 size);

#endif //__ADT_STACK_H__