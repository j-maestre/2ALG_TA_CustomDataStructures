/**
 * @file adt_stack.h
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
	/**
	 * \brief Reset per node in storage
	 * 
	 * \param stack pointer
	 * 
	 * \return s16 kErrorCode_VectorNULL When stack is NULL
	 * \return s16 kErrorCode_StorageNULL When storage is NULL
	 * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*reset)(Stack *stack);

   /**
   * \brief Inserts an element in the first position of the Stack
   * 
   * \param vector pointer
   * \param void* data to insert at first position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_VectorNULL When stack is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When stack is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*push)(Stack *stack, void *data, u16 bytes);

	/**
   * \brief return if the stack is empty
   * 
   * \param stack pointer
   * 
   * \return true if is empty, false if contains any element
   */
	boolean (*isEmpty)(Stack *stack);

	/**
   * \brief return if the stack is full
   * 
   * \param stack pointer
   * 
   * \return true if the tail is equal to capacity, false if not
   */
	boolean (*isFull)(Stack *stack);

	/**
   * \brief Return the maxium number of elements to store
   * 
   * \param stack pointer
   * 
   * \return u16 capacity of the Stack
   */
	u16 (*capacity)(Stack *stack);

   /**
   * \brief Current number of elements in Storage
   * 
   * \param Stack pointer
   * 
   * \return u16 lenght of Stack
   */
	u16 (*length)(Stack *stack);

   /**
   * \brief Returns a reference to the first element inserted on the Stack
   * 
   * \param stack pointer
   * 
   * \return void* NULL When the stack or storage is NULL
   * \return void* pointer to first element of the Stack when the function has done his job
   */
	void* (*top)(Stack *stack);

   /**
   * \brief Concatenates two stacks
   * 
   * \param stack pointer base
   * \param stack_src pointer to concatenate
   * 
   * \return s16 kErrorCode_VectorNULL When one of the Stack is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*concat)(Stack *stack, Stack *stack_src);
	
   /**
   * \brief Resize the capacity of the Stack. Some elements can be lost
   * 
   * \param stack pointer
   * \param u16 new size capacity
   * 
   * \return s16 kErrorCode_VectorNULL When the stack is NULL
   * \return s16 kErrorCode_SizeZERO When the new size is 0
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*resize)(Stack *stack, u16 new_capacity);

   /**
   * \brief Destroys the Stack and his data
   * 
   * \param stack pointer to be destroyed
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*destroy)(Stack *stack);

   /**
   * \brief Extracts the last element inserted on the stack
   * 
   * \param stack pointer
   * 
   * \return void* NULL When stack or storage is NULL
   * \return void* NULL When stack is empty
   * \return void* pointer to the first element of the Stack when the function has done his job
   */
	void* (*pop)(Stack *stack);

	
   /**
   * \brief Prints the features and content of the stack
   * 
   * \param stack pointer
   * 
   * \return void
   */
	void (*print)(Stack *stack);
};



/**
 * \brief Creates a new stack
 * 
 * \param u16 capacity of the Vector 
 * 
 * \return Stack* NULL When capacit equal or less than 0
 * \return Stack* NULL When there isn't memory
 * \return pointer to the created Stack when the function has done his job
 */
Stack* STACK_create(u16 size);

#endif //__ADT_STACK_H__