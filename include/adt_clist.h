/**
 * @file adt_clist.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_CLIST_H__
#define __ADT_CLIST_H__

#include "adt_list.h"

typedef List CList;

 /**
 * \brief Creates a new Circular list
 * 
 * \param u16 capacity of the CList 
 * 
 * \return CList* NULL When capacit equal or less than 0
 * \return CList* NULL When there isn't memory
 * \return pointer to the created CList when the function has done his job
 */
CList* CLIST_create(u16 capacity);

#endif //__ADT_CLIST_H__