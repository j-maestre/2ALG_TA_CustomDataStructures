/**
 * \file memory_manager.h
 * \author Hector Ochanda <ochandoca@esat-alumni.com>
 * \brief A very basic and soft memory manager with memory alignment.
 * 
 */

#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__ 1

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


/**
 * \brief The Memory Manager functions. 
 * 
 */
typedef struct memory_manager_s
{
	void* (*malloc)(size_t size);
	void* (*calloc)(size_t count, size_t size);
	void (*free)(void* ptr);

	void (*status)();
	void (*destroy)();
} MemoryManager;

/**
 * \brief The configuration to init the MemoryManager. 
 * 
 */
typedef struct mm_cfg_s
{
	/**
	* The initial size is going to be allocated.
	*/
	size_t size;

	/**
	* The number of bits that the memory is going to be aligned.
	*/
	size_t alignment;

	void* (*malloc)(size_t size);
	void* (*calloc)(size_t count, size_t size);
	void (*free)(void* ptr);
} MM_Cfg;

/**
 * \brief Some error codes used in the initialization of the MemoryManager.
 * 
 */
enum MM_Status
{
	MM_OK = 0,
	MM_INVALID_ARGUMENTS = -1,
	MM_INVALIDE_CFG = -2,
};


/**
 * \brief Default initialization of the configuration, without setting the pool size. 
 * 
 * \param cfg Pointer to the configuration is going to be initialized.
 */
void MM_Cfg_Init(MM_Cfg* cfg);

/**
 * \brief Creation of the memory manager allocating the size requested.
 * 
 * \param cfg const pointer to the configuration which the memory manager is going created.
 * \return MM_OK
 */
enum MM_Status MemoryManager_Init(const MM_Cfg* cfg);

/**
 * \brief Return the a pointer to the memory manager instance. 
 * 
 * \return MemoryManager* Pointer to the memiry manager instance.
 */
MemoryManager* MemoryManager_Instance();

#ifdef __cplusplus
}
#endif //__cplusplus




#endif //__MEMORY_MANAGER_H__