// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

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
	s16 (*destroy)(Vector *vector);	// Destroys the vector and its data
  s16 (*softReset)(Vector *vector);		// Soft resets vector's data
  s16 (*reset)(Vector *vector);		// Resets vector's data
	s16 (*resize)(Vector *vector, u16 new_size); // Resizes the capacity of the vector. Some elements can be lost

	// State queries
	u16 (*capacity)(Vector *vector);		// returns the maximum number of elemets to store
	u16 (*length)(Vector *vector);			// current number of elements (<= capacity)
	boolean (*isEmpty)(Vector *vector);
	boolean (*isFull)(Vector *vector);

	// Data queries
	void* (*first)(Vector *vector); // Returns a reference to the first element of the vector
	void* (*last)(Vector *vector); // Returns a reference to the last element of the vector
	void* (*at)(Vector *vector, u16 position); // Returns a reference to the element oat a given position

	// Insertion
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes); // Inserts an element in the first position of the vector
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes); // Inserts an element in the last position of the vector
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position); // Inserts an element at the given position of the vector

	// Extraction
	void* (*extractFirst)(Vector *vector); // Extracts the first element of the vector
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
	void* (*extractLast)(Vector *vector); // Extracts the last element of the vector
	void* (*extractAt)(Vector *vector, u16 position); // Extracts the element of the vector at the given position

	// Miscellaneous
	s16 (*concat)(Vector *vector, Vector *vector_src); // Concatenates two vectors
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *)); // Calls to a function from all elements of the vector
	void (*print)(Vector *vector); // Prints the features and content of the vector
};

Vector* VECTOR_create(u16 capacity); // Creates a new vector
#endif //__ADT_VECTOR_H__
