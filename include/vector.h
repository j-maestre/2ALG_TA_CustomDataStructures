
/**
 * @file vector.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__ 1

#include "memory_node.h"

class Vector
{
private:
  Vector(u16 size);
  Vector(const Vector& other);
  Vector(Vector&& other);

public:
  ~Vector();
	
  Vector& operator =(const Vector& other);
  Vector& operator =(Vector&& other);

  /**
 * \brief Creates a new Vector
 * 
 * \param u16 capacity of the Vector 
 * 
 * \return CVector* NULL When capacit equal or less than 0
 * \return CVector* NULL When there isn't memory
 * \return pointer to the created Vector when the function has done his job
 */
  static Vector* Create(u16 size);
	
/**
   * \brief Destroys the Vector and his data
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 destroy();
	    /**
   * \brief Soft reset per node in his storage
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 softReset();
	
   /**
   * \brief Reset per node in storage
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 reset();
	
  /**
   * \brief Reset per node in storage
   * 
   * \param u16 new size capacity
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 resize(u16 new_size);
	   
  /**
   * \brief Return the maxium number of elements to store
   * 
   * \return u16 capacity of the Vector
   */
	u16 capacity() const;
	  
   /**
   * \brief Current number of elements in Storage
   * 
   * \return u16 lenght of Vector
   */
	u16 length() const;
	    
  /**
   * \brief return if the vector is empty
   * 
   * \return true if is empty, false if contains any element
   */
	boolean isEmpty() const;
	  
    /**
   * \brief return if the vector is full
   * 
   * \return true if the tail is equal to capacity, false if not
   */
	boolean isFull() const;
	  
   /**
   * \brief Returns a reference to the first element of the Vector
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* pointer to first element of the Vector
   *               When the function has done his job
   */
	void* first();
	    
  /**
   * \brief Returns a reference to the last element of the Vector
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the vector is empty
   * \return void* pointer to last element of the Vector
   *               When the function has done his job
   */
	void* last();
	    
   /**
   * \brief Returns a reference to the element at a given position
   * 
   * \param u16 position to get the reference
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element of the 
   *               Vector in wanted position
   *               When the function has done his job
   */
	void* at(u16 position);
	    
  /**
   * \brief Inserts an element in the first position of the Vector
   * 
   * \param void* data to insert at first position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When vector is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 insertFirst(void *data, u16 bytes);
	    
  /**
   * \brief Inserts an element in the last position of the Vector
   * 
   * \param void* data to insert at last position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When vector is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 insertLast(void *data, u16 bytes);
	    
   /**
   * \brief Inserts an element at the given position of the Vector
   * 
   * \param void* data to insert at gived position
   * \param u16 bytes size of data to insert
   * \param u16 position to insert the data
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When vector is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 insertAt(void *data, u16 bytes, u16 position);
	    
  /**
   * \brief Extracts the first element of the vector
   * 
   * 
   * \return void* NULL When vector or storage is NULL
   * \return void* NULL When vector is empty
   * \return void* pointer to the first element of the Vector
   *               When the function has done his job
   */
	void* extractFirst();
    
  /**
  * \brief Extracts the last element of the vector
  * 
  * \return void* NULL When Vector or storage is NULL
  * \return void* NULL When Vector is empty
  * \return void* pointer to the last element of the vector
  *               When the function has done his job
  */
	void* extractLast();
	  
    /**
   * \brief Extracts the element of the Vector at the given position
   * 
   * \param u16 position to extract the element of the vector
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element in the wanted position
   *               When the function has done his job
   */
	void* extractAt(u16 position);

   /**
   * \brief Concatenates two vectors
   * 
   * \param vector_src pointer to concatenate
   * 
   * \return s16 kErrorCode_VectorNULL When one of the M NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 concat(Vector *vector_src);

	  /**
	 * \brief Calls to a function from all elements of the Vector
   * 
   * \param callback pointer to call per each data in Storage
   * 
   * \return s16 kErrorCode_VectorNULL When one of the Vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_CallBackNULL When callback is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 traverse(void (*callback)(MemoryNode *));
	  
  /**
	 * \brief return pointer to the storage
   * 
   *
   * \return MemoryNode* to storage
	 */
	MemoryNode* data();
	
     /**
   * \brief Prints the features and content of the vector
   * 
   * 
   * \return void
   */
	void print();

	void* operator new(size_t count);
	void operator delete(void *ptr);

	void* operator new[](size_t count);
	void operator delete[](void *ptr, size_t count);
	
protected:
	u16 head_;
	u16 tail_;
	u16 capacity_;
	MemoryNode *storage_;
};

#endif //__VECTOR_H__