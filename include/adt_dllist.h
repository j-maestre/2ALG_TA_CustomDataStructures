// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_dllist.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_DLLIST_H__
#define __ADT_DLLIST_H__

#include "adt_list.h"

typedef List DLList;

 /**
 * \brief Creates a new Double linked list
 * 
 * \param u16 capacity of the DLList 
 * 
 * \return DLList* NULL When capacit equal or less than 0
 * \return DLList* NULL When there isn't memory
 * \return pointer to the created DLList when the function has done his job
 */
DLList *DLLIST_create(u16 capacity);

#endif //__ADT_DLLIST_H__
