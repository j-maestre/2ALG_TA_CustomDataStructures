
/**
 * @file stack.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __STACK_H__
#define __STACK_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"
#include "vector.h"

class Stack
{
private:
	Stack(u16 size);
	Stack(const Stack& other) = delete;
	Stack(Stack&& other);

public:
	~Stack();

	Stack& operator =(const Stack& other) = delete;
	Stack& operator =(Stack&& other);

	/**
 * \brief Creates a new stack
 * 
 * \param u16 capacity of the Vector 
 * 
 * \return Stack* NULL When capacit equal or less than 0
 * \return Stack* NULL When there isn't memory
 * \return pointer to the created Stack when the function has done his job
 */
	static Stack* Create(u16 size);

/**
	 * \brief Reset per node in storage
	 * 
	 * \return s16 kErrorCode_VectorNULL When stack is NULL
	 * \return s16 kErrorCode_StorageNULL When storage is NULL
	 * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 reset();
	
   /**
   * \brief Inserts an element in the first position of the Stack
   * 
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
	s16 push(void* data, u16 bytes);
	
	/**
   * \brief return if the stack is empty
   * 
   * \return true if is empty, false if contains any element
   */
	boolean isEmpty();
	
	/**
   * \brief return if the stack is full
   * 
   * \return true if the tail is equal to capacity, false if not
   */
	boolean isFull();
	
	/**
   * \brief Return the maxium number of elements to store
   * 
   * \return u16 capacity of the Stack
   */
	u16 capacity();
	
   /**
   * \brief Current number of elements in Storage
   * 
   * 
   * \return u16 lenght of Stack
   */
	u16 length();
	
   /**
   * \brief Returns a reference to the first element inserted on the Stack
   * 
   * \return void* NULL When the stack or storage is NULL
   * \return void* pointer to first element of the Stack when the function has done his job
   */
	void* top();
	
   /**
   * \brief Concatenates two stacks
   * 
   * \param stack_src pointer to concatenate
   * 
   * \return s16 kErrorCode_VectorNULL When one of the Stack is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 concat(Stack* stack_src);
		
   /**
   * \brief Resize the capacity of the Stack. Some elements can be lost
   * 
   * \param u16 new size capacity
   * 
   * \return s16 kErrorCode_VectorNULL When the stack is NULL
   * \return s16 kErrorCode_SizeZERO When the new size is 0
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 resize(u16 new_capacity);
	
   /**
   * \brief Destroys the Stack and his data
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 destroy();
	
   /**
   * \brief Extracts the last element inserted on the stack
   * 
   * \return void* NULL When stack or storage is NULL
   * \return void* NULL When stack is empty
   * \return void* pointer to the first element of the Stack when the function has done his job
   */
	void* pop();
		
   /**
   * \brief Prints the features and content of the stack
   * 
   * \return void
   */
	void print();

	void* operator new(size_t count);
	void operator delete(void *ptr);

	void* operator new[](size_t count);
	void operator delete[](void* ptr, size_t count);

protected:
	Vector *storage_;
};

#endif //__STACK_H__