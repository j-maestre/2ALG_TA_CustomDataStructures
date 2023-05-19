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

	static Stack* Create(u16 size);

	s16 reset();
	s16 push(void* data, u16 bytes);
	boolean isEmpty();
	boolean isFull();
	u16 capacity();
	u16 length();
	void* top();
	s16 concat(Stack* stack_src);
	s16 resize(u16 new_capacity);
	s16 destroy();
	void* pop();
	void print();

	void* operator new(size_t count);
	void operator delete(void *ptr);

	void* operator new[](size_t count);
	void operator delete[](void* ptr, size_t count);

protected:
	Vector *storage_;
};

#endif //__STACK_H__