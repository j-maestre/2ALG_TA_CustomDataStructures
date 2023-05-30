// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_movable_vector.h
 * @author Jose Maria Maestre <maestrequi@esat-alumni.com>
 */

#ifndef __ADT_MOVABLE_VECTOR_H__
#define __ADT_MOVABLE_VECTOR_H__

#include "adt_vector.h"

typedef Vector MVector;

 /**
 * \brief Creates a new Movable Vector
 * 
 * \param u16 capacity of the Movable Vector 
 * 
 * \return MVector* NULL When capacit equal or less than 0
 * \return MVector* NULL When there isn't memory
 * \return pointer to the created MVector when the function has done his job
 */
MVector* MVECTOR_create(u16 capacity);

#endif //__ADT_MOVABLE_VECTOR_H__
