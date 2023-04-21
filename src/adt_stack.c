#include "EDK_MemoryManager/edk_memory_manager.h"

#include "common_def.h"

#include "adt_memory_node.h"
#include "adt_vector.h"

#include "adt_stack.h"

static s16 STACK_reset(Stack* stack);
static s16 STACK_push(Stack* stack, void* data, u16 bytes);
static boolean STACK_isEmpty(Stack* stack);
static boolean STACK_isFull(Stack *stack);
static u16 STACK_capacity(Stack* stack);
static u16 STACK_length(Stack* stack);
static void* STACK_top(Stack* stack);
static s16 STACK_concat(Stack* stack, Stack* stack_src);
static s16 STACK_resize(Stack *stack, u16 new_size);
static s16 STACK_destroy(Stack* stack);
static void* STACK_pop(Stack* stack);
static void STACK_print(Stack* stack);

struct stack_ops_s stack_ops = {
																	.reset = STACK_reset,
																	.push = STACK_push,
																	.isEmpty = STACK_isEmpty,
																	.isFull = STACK_isFull,
																	.capacity = STACK_capacity,
																	.length = STACK_length,
																	.top = STACK_top,
																	.concat = STACK_concat,
																	.resize = STACK_resize,
																	.destroy = STACK_destroy,
																	.pop = STACK_pop,
																	.print = STACK_print,
};

Stack* STACK_create(u16 size)
{
	if (size == 0)
	{
		return NULL;
	}

	Stack *stack = MM->malloc(sizeof(Stack));
	if (stack == NULL)
	{
		return NULL;
	}

	stack->storage_ = VECTOR_create(size);

	if (stack->storage_ == NULL)
	{
		MM->free(stack);
	}

	stack->ops_ = &stack_ops;

	return stack;
}

s16 STACK_reset(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->reset(stack->storage_);
}

s16 STACK_push(Stack* stack, void* data, u16 bytes)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->insertFirst(stack->storage_, data, bytes);
}

boolean STACK_isEmpty(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->isEmpty(stack->storage_);
}

boolean STACK_isFull(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->isFull(stack->storage_);
}

u16 STACK_capacity(Stack* stack)
{
	if (stack == NULL)
	{
		return 0;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->capacity(stack->storage_);
}

u16 STACK_length(Stack* stack)
{
	if (stack == NULL)
	{
		return 0;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->length(stack->storage_);
}

void* STACK_top(Stack* stack)
{
	if (stack == NULL)
	{
		return NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->first(stack->storage_);
}

s16 STACK_concat(Stack* stack, Stack* stack_src)
{
	if (stack == NULL || stack_src == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->concat(stack->storage_, stack_src->storage_);
}

s16 STACK_resize(Stack* stack, u16 new_size)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->resize(stack->storage_, new_size);
}

s16 STACK_destroy(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	s16 result =  stack->storage_->ops_->destroy(stack->storage_);

	if (result == kErrorCode_Ok)
	{
		MM->free(stack);
	}
	return result;
}

void* STACK_pop(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return stack->storage_->ops_->extractFirst(stack->storage_);
}

void STACK_print(Stack* stack)
{
	if (stack == NULL)
	{
		return kErrorCode_NULL;
	}

	if (stack->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	stack->storage_->ops_->print(stack->storage_);
}