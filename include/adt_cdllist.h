/**
 * @file adt_cdllist.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */


#ifndef __ADT_CLIST_H__
#define __ADT_CLIST_H__

#include "adt_list.h"

typedef List CDLList;

 /**
 * \brief Creates a new Circular Double Linked list
 * 
 * \param u16 capacity of the CDLList 
 * 
 * \return CVector* NULL When capacit equal or less than 0
 * \return CVector* NULL When there isn't memory
 * \return pointer to the created CVector when the function has done his job
 */
CDLList* CDLLIST_create(u16 capacity);

#endif //__ADT_CLIST_H__