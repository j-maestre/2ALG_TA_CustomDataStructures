// common_def.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__ 1

#define VERBOSE_

typedef enum {
  kErrorCode_Ok = 0,
  kErrorCode_Null = -1,
  kErrorCode_Memory = -2,
  kErrorCode_MemoryNodeNULL = -3,
  kErrorCode_DataNULL = -4,
  kErrorCode_ZeroBytes = -5,
  kErrorCode_NoMemory = -6,
  kErrorCode_VectorNULL = -7,
  kErrorCode_StorageNULL = -8,
  kErrorCode_SizeZERO = -9,
  kErrorCode_VectorTailExceedsCapacity = -10,
  kErrorCode_VectorPositionExceedsCapacity = -11,
  kErrorCode_VectorPositionExceedsTail = -12,
} ErrorCode;

#endif // __COMMON_DEF_H__