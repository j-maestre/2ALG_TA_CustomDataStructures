/**
 *
 *  @brief ESAT Development Kit (EDK) Memory Manager header file.
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


#ifndef __EDK_MEMORY_MANAGER_H__
#define __EDK_MEMORY_MANAGER_H__ 1

#include "edk_platform_types.h"

typedef struct edk_memory_manager_s {
  struct memory_manager_ops_s *ops_;
} EDK_MemoryManager;

struct memory_manager_ops_s {
  void* (*malloc)(int size);
  void* (*calloc)(int size);
  void (*free)(void *ptr);
  void (*status)();
  void (*destroy)();
};

EDK_MemoryManager* EDK_MemMngrInstance();
#define MM (EDK_MemMngrInstance()->ops_)

#endif //__EDK_MEMORY_MANAGER_H__
