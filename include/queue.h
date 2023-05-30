
/**
 * @file queue.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"
#include "list.h"

class Queue
{
private:
  Queue(u16 size);
  Queue(const Queue& other) = delete;
  Queue(Queue&& other);
  
public:
  ~Queue();

  Queue& operator =(const Queue& other) = delete;
  Queue& operator =(Queue&& other);

   /**
 * \brief Creates a new queue
 * 
 * \param u16 capacity of the Queue 
 * 
 * \return Queue* NULL When capacit equal or less than 0
 * \return Queue* NULL When there isn't memory
 * \return pointer to the created Queue when the function has done his job
 */
  static Queue* Create(u16 size);
  
  /**
	 * \brief Reset per node in storage
	 * 
	 * 
	 * \return s16 kErrorCode_NULL When queue is NULL
	 * \return s16 kErrorCode_StorageNULL When storage is NULL
	 * \return s16 kErrorCode_Ok When the function has done his job
	*/
  s16 reset();
  
	/**
	 * \brief Inserts an element in the last position of the Queue
	 * 
	 * \param void* data to insert at last position
	 * \param u16 bytes size of data to insert
	 * 
	 * \return s16 kErrorCode_NULL When queue is NULL
	 * \return s16 kErrorCode_StorageNULL When storage is NULL
	 * \return s16 kErrorCode_DataNULL When data is NULL
	 * \return s16 kErrorCode_ZeroBytes When bytes is 0
	 * \return s16 kErrorCode_ListFull When queue is full
	 * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 enqueue(void *data, u16 bytes);
  
	/**
	 * \brief return true if the queue is empty
	 * 
	 * 
	 * \return true if is empty, false if contains any element
	*/
  boolean isEmpty();
  
	/**
	 * \brief return if the queue is full
	 * 
	 * 
	 * \return true if the tail is equal to capacity, false if not or something is null
   */
  boolean isFull();
  
	 /**
	 * \brief Return the maxium number of elements to store
	 * 
	 * 
	 * \return u16 capacity of the Queue
   */
  u16 capacity();
  
   /**
	 * \brief Resize the capacity of the Queue. Some elements can be lost
	 * 
	 * \param u16 new size capacity
	 * 
	 * \return s16 kErrorCode_ListNULL When the queue is NULL
	 * \return s16 kErrorCode_SizeZERO When the new size is 0
	 * \return s16 kErrorCode_NoMemory When there isn't memory
   */
  s16 resize(u16 new_size);
  
	/**
	 * \brief Extracts the last element inserted
	 * 
	 * 
	 * \return void* NULL When Queue or storage is NULL
	 * \return void* NULL When Queue is empty
	 * \return void* pointer to the last element of the queue when the function has done his job
  */
  void* dequeue();
  	/**
	 * \brief Current number of elements in Storage
	 * 
	 * 
	 * \return u16 lenght of Queue
   */
  u16 length();
  
	 /**
	 * \brief Returns a reference to the last element inserted on the queue
	 * 
	 * 
	 * \return void* NULL When the queue or storage is NULL
	 * \return void* pointer to last element inserted of the Queue when the function has done his job
   */
  void* front();
  
	/**
	 * \brief Returns a reference to the first element inserted on the queue
	 * 
	 * \return void* NULL When the queue or storage is NULL
	 * \return void* pointer to first element inserted of the Queue when the function has done his job
   */
  void* back();
  
	/**
	 * \brief Concatenates two queues
     * 
	 * \param queue_src pointer to concatenate
     * 
     * \return s16 kErrorCode_ListNULL When one of the Queue is NULL
     * \return s16 kErrorCode_StorageNULL When storage is NULL
     * \return s16 kErrorCode_NoMemory When there isn't memory
     * \return s16 kErrorCode_Ok When the function has done his job
	*/
  s16 concat(Queue *queue_src);
  
	/**
   * \brief Destroys the Queue and his data
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 destroy();
  
	/**
   * \brief Prints the features and content of the queue
   * 
   * \return void
   */
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);
  
protected:
  List *storage_;
};

#endif //__QUEUE_H__