/**
 *
 *  @brief ESAT Development Kit (EDK) Memory Manager platform types.
 *
 *  @brief Multithreading and cross-platform integration:
 *         Windows OS
 *         Linux OS
 *         Mac OS
 *
 *  @author Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2020/21
 *  @subject Algorithms & Data Structures
 *
 *  All rights are reserved.
 *
 */


#ifndef __EDK_PLATFORM_TYPES_H__
#define __EDK_PLATFORM_TYPES_H__ 1

#include <stdint.h>

typedef uint8_t 		   u8;
typedef int_least8_t 	 s8;
typedef uint16_t 		   u16;
typedef int_least16_t  s16;
typedef uint32_t 		   u32;
typedef int_least32_t  s32;
typedef uint64_t 		   u64;
typedef int_least64_t	 s64;

typedef uint8_t 		   boolean;
#define True 			     1
#define False 			   0

typedef uint32_t		   BIT_FIELD;

#endif //__EDK_PLATFORM_TYPES_H__
