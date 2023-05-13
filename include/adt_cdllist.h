/**
 * @file adt_memory_node.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */


#ifndef __ADT_CLIST_H__
#define __ADT_CLIST_H__

#include "adt_list.h"

typedef List CDLList;

CDLList* CDLLIST_create(u16 capacity);

#endif //__ADT_CLIST_H__