// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_list.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

typedef struct adt_list_s {
	MemoryNode *head_;
	MemoryNode *tail_;
	u16 capacity_;
	u16 lenght_;
	struct list_ops_s *ops_;
} List;


struct list_ops_s {

  /**
   * \brief Destroys the List and his data
   * 
   * \param list pointer to be destroyed
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*destroy)(List *list);

  /**
   * \brief Soft reset per node in his storage
   * 
   * \param list pointer to soft reset
   * 
   * \return s16 kErrorCode_ListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 (*softReset)(List *list);

  /**
   * \brief Reset per node in storage
   * 
   * \param list pointer to reset
   * 
   * \return s16 kErrorCode_ListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 (*reset)(List *list);

   /**
   * \brief Resize the capacity of the List. Some elements can be lost
   * 
   * \param list pointer to be resized
   * \param u16 new size capacity
   * 
   * \return s16 kErrorCode_ListNULL When the list is NULL
   * \return s16 kErrorCode_SizeZERO When the new size is 0
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*resize)(List *list, u16 new_size);

	 /**
   * \brief Return the maxium number of elements to store
   * 
   * \param list pointer
   * 
   * \return u16 capacity of the List
   */
	u16 (*capacity)(List *list);

  /**
   * \brief Current number of elements in Storage
   * 
   * \param List pointer
   * 
   * \return u16 lenght of List
   */
	u16 (*length)(List *list);

  /**
   * \brief return true if the list is empty
   * 
   * \param list pointer
   * 
   * \return true if is empty, false if contains any element
   */
	boolean (*isEmpty)(List *list);

  /**
   * \brief return if the list is full
   * 
   * \param list pointer
   * 
   * \return true if the tail is equal to capacity, false if not
   */
	boolean (*isFull)(List *list);

  /**
   * \brief Returns a reference to the first element of the List
   * 
   * \param list pointer
   * 
   * \return void* NULL When the list or storage is NULL
   * \return void* pointer to first element of the List
   *               When the function has done his job
   */
	void* (*first)(List *list);

  /**
   * \brief Returns a reference to the last element of the List
   * 
   * \param list pointer
   * 
   * \return void* NULL When the list or storage is NULL
   * \return void* NULL When the list is empty
   * \return void* pointer to last element of the List
   *               When the function has done his job
   */
	void* (*last)(List *list);

   /**
   * \brief Returns a reference to the element at a given position
   * 
   * \param list pointer
   * \param u16 position to get the reference
   * 
   * \return void* NULL When the list or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element of the 
   *               list in wanted position
   *               When the function has done his job
   */
	void* (*at)(List *list, u16 position);

   /**
   * \brief Inserts an element in the first position of the List
   * 
   * \param list pointer to insert
   * \param void* data to insert at first position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_ListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_ListFull When list is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*insertFirst)(List *list, void *data, u16 bytes);

  /**
   * \brief Inserts an element in the last position of the List
   * 
   * \param list pointer
   * \param void* data to insert at last position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_ListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_ListFull When list is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*insertLast)(List *list, void *data, u16 bytes);

  /**
   * \brief Inserts an element at the given position of the List
   * 
   * \param list pointer
   * \param void* data to insert at gived position
   * \param u16 bytes size of data to insert
   * \param u16 position to insert the data
   * 
   * \return s16 kErrorCode_ListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_ListFull When list is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*insertAt)(List *list, void *data, u16 bytes, u16 position);
  
  /**
  * \brief Extracts the first element of the list
  * 
  * \param list pointer
  * 
  * \return void* NULL When List or storage is NULL
  * \return void* NULL When List is empty
  * \return void* pointer to the last element of the list
  *               When the function has done his job
  */
	void* (*extractFirst)(List *list);

	/**
  * \brief Extracts the last element of the list
  * 
  * \param list pointer
  * 
  * \return void* NULL When List or storage is NULL
  * \return void* NULL When List is empty
  * \return void* pointer to the last element of the list
  *               When the function has done his job
  */
	void* (*extractLast)(List *list);

  /**
   * \brief Extracts the element of the List at the given position
   * 
   * \param list pointer
   * \param u16 position to extract the element of the list
   * 
   * \return void* NULL When the list or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element in the wanted position
   *               When the function has done his job
   */
	void* (*extractAt)(List *list, u16 position);

	/**
	 * \brief Concatenates two list
   * 
	 * \param list pointer base
	 * \param list_src pointer to concatenate
   * 
   * \return s16 kErrorCode_ListNULL When one of the List is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 (*concat)(List *list, List *lisrt_src);

  /**
	 * \brief Calls to a function from all elements of the List
   * 
	 * \param list pointer
   * \param callback pointer to call per each data in Storage
   * 
   * \return s16 kErrorCode_ListNULL When one of the List is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_CallBackNULL When callback is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 (*traverse)(List *list, void (*callback)(MemoryNode *));

  /**
   * \brief Prints the features and content of the list
   * 
   * \param list pointer
   * 
   * \return void
   */
	void (*print)(List *list);
};
  /**
 * \brief Creates a new list
 * 
 * \param u16 capacity of the List 
 * 
 * \return List* NULL When capacit equal or less than 0
 * \return List* NULL When there isn't memory
 * \return pointer to the created List
 *         When the function has done his job
 */

List *LIST_create(u16 capacity);

#endif //__ADT_LIST_H__
