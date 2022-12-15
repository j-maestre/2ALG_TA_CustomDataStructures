// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_vector.h
 * @author Xema Maestre <maestrequi@esat-alumni.com>
 */

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "adt_memory_node.h"

typedef struct adt_vector_s {
	u16 head_;
	u16 tail_; // Corresponds to the first free place of the vector
	u16 capacity_;
	MemoryNode *storage_;
	struct vector_ops_s *ops_;
} Vector;


struct vector_ops_s {
  /**
   * \brief Destroys the Vector and his data
   * 
   * \param vector pointer to be destroyed
   * 
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*destroy)(Vector *vector);

  /**
   * \brief Soft reset per node in his storage
   * 
   * \param vector pointer
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 (*softReset)(Vector *vector);

  /**
   * \brief Reset per node in storage
   * 
   * \param vector pointer
   * 
   * \return s16 kErrorCode_VectorNULL When vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
   */
  s16 (*reset)(Vector *vector);

  /**
   * \brief Resize the capacity of the Vector. Some elements can be lost
   * 
   * \param vector pointer
   * \param u16 new size capacity
   * 
   * \return s16 kErrorCode_VectorNULL When the vector is NULL
   * \return s16 kErrorCode_SizeZERO When the new size is 0
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*resize)(Vector *vector, u16 new_size);


  /**
   * \brief Return the maxium number of elements to store
   * 
   * \param vector pointer
   * 
   * \return u16 capacity of the Vector
   */
	u16 (*capacity)(Vector *vector);

  /**
   * \brief Current number of elements in Storage
   * 
   * \param Vector pointer
   * 
   * \return u16 lenght of Vector
   */
	u16 (*length)(Vector *vector);

  /**
   * \brief return if the vector is empty
   * 
   * \param vector pointer
   * 
   * \return true if is empty, false if contains any element
   */
	boolean (*isEmpty)(Vector *vector);

  /**
   * \brief return if the vector is full
   * 
   * \param vector pointer
   * 
   * \return true if the tail is equal to capacity, false if not
   */
	boolean (*isFull)(Vector *vector);

  /**
   * \brief Returns a reference to the first element of the Vector
   * 
   * \param vector pointer
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* pointer to first element of the Vector
   *               When the function has done his job
   */
	void* (*first)(Vector *vector);

  /**
   * \brief Returns a reference to the last element of the Vector
   * 
   * \param vector pointer
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the vector is empty
   * \return void* pointer to last element of the Vector
   *               When the function has done his job
   */
	void* (*last)(Vector *vector);

   /**
   * \brief Returns a reference to the element at a given position
   * 
   * \param vector pointer
   * \param u16 position to get the reference
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element of the 
   *               Vector in wanted position
   *               When the function has done his job
   */
	void* (*at)(Vector *vector, u16 position);

  /**
   * \brief Inserts an element in the first position of the Vector
   * 
   * \param vector pointer
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
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes);

  /**
   * \brief Inserts an element in the last position of the Vectorç
   * 
   * \param vector pointer
   * \param void* data to insert at last position
   * \param u16 bytes size of data to insert
   * 
   * \return s16 kErrorCode_VectorNULL When vetor is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When vector is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes);

   /**
   * \brief Inserts an element at the given position of the Vector
   * 
   * \param vector pointer
   * \param void* data to insert at gived position
   * \param u16 bytes size of data to insert
   * \param u16 position to insert the data
   * 
   * \return s16 kErrorCode_VectorNULL When vetor is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_DataNULL When data is NULL
   * \return s16 kErrorCode_ZeroBytes When bytes is 0
   * \return s16 kErrorCode_VectorFull When vector is full
   * \return s16 kErrorCode_Ok When the function has done his job
   */
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position);

  /**
   * \brief Extracts the first element of the vector
   * 
   * \param vector pointer
   * 
   * \return void* NULL When vector or storage is NULL
   * \return void* NULL When vector is empty
   * \return void* pointer to the first element of the Vector
   *               When the function has done his job
   */
	void* (*extractFirst)(Vector *vector);
  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(Vector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */

 /**
  * \brief Extracts the last element of the vector
  * 
  * \param vector pointer
  * 
  * \return void* NULL When Vector or storage is NULL
  * \return void* NULL When Vector is empty
  * \return void* pointer to the last element of the vector
  *               When the function has done his job
  */
	void* (*extractLast)(Vector *vector);

  /**
   * \brief Extracts the element of the Vector at the given position
   * 
   * \param vector pointer
   * \param u16 position to extract the element of the vector
   * 
   * \return void* NULL When the vector or storage is NULL
   * \return void* NULL When the position is greater or equal of tail
   * \return void* pointer to the element in the wanted position
   *               When the function has done his job
   */
	void* (*extractAt)(Vector *vector, u16 position);

	/**
	 * \brief Concatenates two vectors
   * 
	 * \param vector pointer base
	 * \param vector pointer to concatenate
   * 
   * \return s16 kErrorCode_VectorNULL When one of the Vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_NoMemory When there isn't memory
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 (*concat)(Vector *vector, Vector *vector_src);

  /**
	 * \brief Calls to a function from all elements of the Vector
   * 
	 * \param vector pointer
   * \param callback pointer to call per each data in Storage
   * 
   * \return s16 kErrorCode_VectorNULL When one of the Vector is NULL
   * \return s16 kErrorCode_StorageNULL When storage is NULL
   * \return s16 kErrorCode_CallBackNULL When callback is NULL
   * \return s16 kErrorCode_Ok When the function has done his job
	 */
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *));

  /**
   * \brief Prints the features and content of the vector
   * 
   * \param vector pointer
   * 
   * \return void
   */
	void (*print)(Vector *vector);
};

/**
 * \brief Creates a new vector
 * 
 * \param u16 capacity of the Vector 
 * 
 * \return Vector* NULL When capacit equal or less than 0
 * \return Vector* NULL When there isn't memory
 * \return pointer to the created Vector
 *         When the function has done his job
 */
Vector* VECTOR_create(u16 capacity);
#endif //__ADT_VECTOR_H__
