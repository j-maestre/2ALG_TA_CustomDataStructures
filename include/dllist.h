
/**
 * @file dllist.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef  __DLLIST_H__
#define __DLLIST_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

#include "memory_node.h"

class DLList
{
private:
  DLList(u16 size);
  DLList(const DLList& other) = delete;
  DLList(DLList&& other);

public:
  ~DLList();

  DLList& operator =(const DLList& other) = delete;
  DLList& operator =(DLList&& other);

   /**
   * \brief Creates a new dlist
   * 
   * \param u16 capacity of the DList 
   * 
   * \return DList* NULL When capacit equal or less than 0
   * \return DList* NULL When there isn't memory
   * \return pointer to the created DList
   *         When the function has done his job
   */
  static DLList* Create(u16 size);

   /**
   * \brief Destroys the DList and his data
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 destroy();

    /**
   * \brief Soft reset per node in his storage
   * 
   * \return s16 kErrorCode_DListNULL When dlist is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 softReset();

    /**
   * \brief Reset per node in storage
   * 
   * 
   * \return s16 kErrorCode_DListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 reset();

  
   /**
   * \brief Resize the capacity of the DList. Some elements can be lost
   * 
   * \param u16 new size capacity
   * 
   * \return s16 kErrorCode_ListNULL When the dlist is NULL
   * \return s16 kErrorCode_SizeZERO When the new size is 0
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 resize(u16 new_size);

  
	 /**
   * \brief Return the maxium number of elements to store
   * 
   * \return u16 capacity of the DList
   */
  u16 capacity();

  
  /**
   * \brief Current number of elements in Storage
   * 
   * \return u16 lenght of DList
   */
  u16 length();

  
  /**
   * \brief return true if the dlist is empty
   * 
   * \return true if is empty, false if contains any element
   */
  boolean isEmpty();

  
  /**
   * \brief return if the dlist is full
   * 
   * \return true if the tail is equal to capacity, false if not
   */
  boolean isFull();

  
  /**
   * \brief Returns a reference to the first element of the DList
   * 
   * \return void* NULL When the dlist or storage is NULL
   * \return void* pointer to first element of the DList
   *               When the function has done his job
   */
  MemoryNode* first();

  
  /**
   * \brief Returns a reference to the last element of the DList
   * 
   * \return void* NULL When the dlist or storage is NULL
   * \return void* NULL When the dlist is empty
   * \return void* pointer to last element of the List
   *               When the function has done his job
   */
  MemoryNode* last();

  
   /**
   * \brief Returns a reference to the element at a given position
   * 
   * \param u16 position to get the reference
   * 
   * \return void* NULL When the dlist or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element of the 
   *               list in wanted position
   *               When the function has done his job
   */
  MemoryNode* at(u16 position);

  
   /**
   * \brief Inserts an element in the first position of the DList
   * 
   * \param void* data to insert at first position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_DListNULL When list is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_DListFull When list is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 insertFirst(void *data, u16 bytes);

  
  /**
   * \brief Inserts an element in the last position of the DList
   * 
   * \param void* data to insert at last position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_ListNULL When dlist is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_ListFull When dlist is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 insertLast(void *data, u16 bytes);

    /**
   * \brief Inserts an element at the given position of the D
   * 
   * \param void* data to insert at gived position
   * \param u16 bytes size of data to insert
   * \param u16 position to insert the data
   * 
   * \return s16 kErrorCode_ListNULL When dlist is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_ListFull When dlist is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 insertAt(void *data, u16 bytes, u16 position);

    
  /**
  * \brief Extracts the first element of the dlist
  * 
  * \return void* NULL When DList or storage is NULL
  * \return void* NULL When DList is empty
  * \return void* pointer to the last element of the dlist
  *               When the function has done his job
  */
  MemoryNode* extractFirst();

  
	/**
  * \brief Extracts the last element of the dlist
  * 
  * \return void* NULL When DList or storage is NULL
  * \return void* NULL When DList is empty
  * \return void* pointer to the last element of the list
  *               When the function has done his job
  */
  MemoryNode* extractLast();

  
  /**
   * \brief Extracts the element of the DList at the given position
   * 
   * \param u16 position to extract the element of the dlist
   * 
   * \return void* NULL When the dlist or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element in the wanted position
   *               When the function has done his job
   */
  MemoryNode* extractAt(u16 position);

  
	/**
	 * \brief Concatenates two dlist
   * 
	 * \param list_src pointer to concatenate
   * 
   * \return s16 kErrorCode_ListNULL When one of the DList is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
  s16 concat(DLList *list_src);

  
  /**
	 * \brief Calls to a function from all elements of the DList
   * 
   * \param callback pointer to call per each data in Storage
   * 
   * \return s16 kErrorCode_DListNULL When one of the DList is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_CallBackNULL When callback is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
  s16 traverse(void (*callback)(MemoryNode *));

  
  /**
   * \brief Prints the features and content of the list
   * 
   * \return void
   */
  void print();

  void* operator new(size_t count);
  void operator delete(void *ptr);

  void* operator new[](size_t count);
  void operator delete[](void *ptr, size_t count);

protected:
  
  MemoryNode *head_;
  MemoryNode *tail_;
  u16 capacity_;
  u16 lenght_;
};

#endif //__DLLIST_H__