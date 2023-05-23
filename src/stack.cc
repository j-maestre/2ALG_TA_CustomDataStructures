#include "stack.h"

#include "EDK_MemoryManager/edk_memory_manager.h"
#include "common_def.h"

Stack::Stack(u16 size)
{
	storage_ = Vector::Create(size);
}

Stack::Stack(Stack&& other)
{
	storage_ = other.storage_;
	other.storage_ = nullptr;
}

Stack::~Stack()
{

}

Stack& Stack::operator=(Stack&& other)
{
	if (this != &other)
	{
		storage_ = other.storage_;
		other.storage_ = nullptr;
	}

	return *this;
}

Stack* Stack::Create(u16 size)
{
	return new Stack(size);
}

void* Stack::operator new(size_t count)
{
	return MM->malloc(count);
}

void Stack::operator delete(void* ptr)
{
	MM->free(ptr);
}

void* Stack::operator new[](size_t count)
{
	return MM->malloc(count);
}

void Stack::operator delete[](void* ptr, size_t count)
{
	MM->free(ptr);
}

s16 Stack::reset()
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->reset();
}

s16 Stack::push(void* data, u16 bytes)
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->insertFirst(data, bytes);
}

boolean Stack::isEmpty()
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->isEmpty();
}

boolean Stack::isFull()
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->isFull();
}

u16 Stack::capacity()
{
	if (this == NULL)
	{
		return 0;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->capacity();
}

u16 Stack::length()
{
	if (this == NULL)
	{
		return 0;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->length();
}

void* Stack::top()
{
	if (this == NULL)
	{
		return NULL;
	}

	if (this->storage_ == NULL)
	{
		return NULL;
	}

	return this->storage_->first();
}

s16 Stack::concat(Stack* stack_src)
{
	if (this == NULL || stack_src == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->concat(stack_src->storage_);
}

s16 Stack::resize(u16 new_size)
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	return this->storage_->resize(new_size);
}

s16 Stack::destroy()
{
	if (this == NULL)
	{
		return kErrorCode_NULL;
	}

	if (this->storage_ == NULL)
	{
		return kErrorCode_NULL;
	}

	s16 result = this->storage_->destroy();

	if (result == kErrorCode_Ok)
	{
		delete this;
	}
	return result;
}

void* Stack::pop()
{
	if (this == NULL)
	{
		return NULL;
	}

	if (this->storage_ == NULL)
	{
		return NULL;
	}

	return this->storage_->extractFirst();
}

void Stack::print()
{
	if (this == NULL)
	{
		return;
	}

	if (this->storage_ == NULL)
	{
		return;
	}

	this->storage_->print();
}