// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_vector.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

typedef struct adt_list_s {
	u16 head_;
	u16 tail_;
	u16 capacity_;
	MemoryNode *storage_;
	struct list_ops_s *ops;
} List;


struct list_ops_s {

	s16 (*destroy)(List *list);


  s16 (*softReset)(List *list);


  s16 (*reset)(List *list);

  
	s16 (*resize)(List *list, u16 new_size);

	
	u16 (*capacity)(List *list);


	u16 (*length)(List *list);


	boolean (*isEmpty)(List *list);


	boolean (*isFull)(List *list);


	void* (*first)(List *list);


	void* (*last)(List *list);


	void* (*at)(List *list, u16 position);


	s16 (*insertFirst)(List *list, void *data, u16 bytes);


	s16 (*insertLast)(List *list, void *data, u16 bytes);


	s16 (*insertAt)(List *list, void *data, u16 bytes, u16 position);


	void* (*extractFirst)(List *list);

	
	void* (*extractLast)(List *list);

  
	void* (*extractAt)(List *list, u16 position);

	
	s16 (*concat)(List *list, List *lisrt_src);

  
	s16 (*traverse)(List *list, void (*callback)(MemoryNode *));

  
	void (*print)(List *list);
};

List *LIST_Create(u16 capacity);

#endif //__ADT_LIST_H__
