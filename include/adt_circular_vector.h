// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

/**
 * @file adt_circular_vector.h
 * @author Jose Maria Maestre <maestrequi@esat-alumni.com>
 */

#ifndef __ADT_CIRCULAR_VECTOR_H__
#define __ADT_CIRCULAR_VECTOR_H__

#include "adt_vector.h"

typedef Vector CVector;

 /**
 * \brief Creates a new Circular Vector
 * 
 * \param u16 capacity of the CVector 
 * 
 * \return CVector* NULL When capacit equal or less than 0
 * \return CVector* NULL When there isn't memory
 * \return pointer to the created CVector when the function has done his job
 */
CVector* CVECTOR_create(u16 capacity);

#endif //__ADT_MOVABLE_VECTOR_H__