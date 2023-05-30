/**
 * @file adt_queue.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

typedef struct adt_queue_s {
	struct adt_list_s* storage_;
	struct queue_ops_s* ops_;
} Queue;

struct queue_ops_s {
	/**
	 * \brief Reset per node in storage
	 * 
	 * \param queue pointer
	 * 
	 * \return s16 kErrorCode_NULL When queue is NULL
	 * \return s16 kErrorCode_StorageNULL When storage is NULL
	 * \return s16 kErrorCode_Ok When the function has done his job
	*/
	s16 (*reset)(Queue *queue);

	/**
	 * \brief Inserts an element in the last position of the Queue
	 * 
	 * \param queue pointer
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
	s16 (*enqueue)(Queue *queue, void *data, u16 bytes);

	/**
	 * \brief return true if the queue is empty
	 * 
	 * \param queue pointer
	 * 
	 * \return true if is empty, false if contains any element
	*/
	boolean (*isEmpty)(Queue *queue);

	/**
	 * \brief return if the queue is full
	 * 
	 * \param queue pointer
	 * 
	 * \return true if the tail is equal to capacity, false if not or something is null
   */
	boolean (*isFull)(Queue *queue);

	 /**
	 * \brief Return the maxium number of elements to store
	 * 
	 * \param queue pointer
	 * 
	 * \return u16 capacity of the Queue
   */
	u16 (*capacity)(Queue *queue);

	
   /**
	 * \brief Resize the capacity of the Queue. Some elements can be lost
	 * 
	 * \param queue pointer to be resized
	 * \param u16 new size capacity
	 * 
	 * \return s16 kErrorCode_ListNULL When the queue is NULL
	 * \return s16 kErrorCode_SizeZERO When the new size is 0
	 * \return s16 kErrorCode_NoMemory When there isn't memory
   */
	s16 (*resize)(Queue *queue, u16 new_size);

	/**
	 * \brief Extracts the last element inserted
	 * 
	 * \param queue pointer
	 * 
	 * \return void* NULL When Queue or storage is NULL
	 * \return void* NULL When Queue is empty
	 * \return void* pointer to the last element of the queue when the function has done his job
  */
	void* (*dequeue)(Queue *queue);

	/**
	 * \brief Current number of elements in Storage
	 * 
	 * \param Queue pointer
	 * 
	 * \return u16 lenght of Queue
   */
	u16 (*length)(Queue *queue);

	 /**
	 * \brief Returns a reference to the last element inserted on the queue
	 * 
	 * \param queue pointer
	 * 
	 * \return void* NULL When the queue or storage is NULL
	 * \return void* pointer to last element inserted of the Queue when the function has done his job
   */
	void* (*front)(Queue *queue);

	/**
	 * \brief Returns a reference to the first element inserted on the queue
	 * 
	 * \param queue pointer
	 * 
	 * \return void* NULL When the queue or storage is NULL
	 * \return void* pointer to first element inserted of the Queue when the function has done his job
   */
	void* (*back)(Queue *queue);

	/**
	 * \brief Concatenates two queues
     * 
	 * \param queue pointer base
	 * \param queue_src pointer to concatenate
     * 
     * \return s16 kErrorCode_ListNULL When one of the Queue is NULL
     * \return s16 kErrorCode_StorageNULL When storage is NULL
     * \return s16 kErrorCode_NoMemory When there isn't memory
     * \return s16 kErrorCode_Ok When the function has done his job
	*/
	s16 (*concat)(Queue *queue, Queue *queue_src);

	/**
   * \brief Destroys the Queue and his data
   * 
   * \param queue pointer to be destroyed
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*destroy)(Queue *queue);

	/**
   * \brief Prints the features and content of the queue
   * 
   * \param queue pointer
   * 
   * \return void
   */
	void (*print)(Queue *queue);
};

 /**
 * \brief Creates a new queue
 * 
 * \param u16 capacity of the Queue 
 * 
 * \return Queue* NULL When capacit equal or less than 0
 * \return Queue* NULL When there isn't memory
 * \return pointer to the created Queue when the function has done his job
 */
Queue* QUEUE_create(u16 size);

#endif //__ADT_QUEUE_H__