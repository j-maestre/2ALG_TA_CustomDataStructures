#include "memory_manager.h"

#include "data_structures/cc_hashtable.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef unsigned char byte;

typedef struct mm_data_s
{
	byte* start;
	byte* end;
	size_t size;
	size_t alloced_size;
	size_t alignment;

	CC_HashTable* alloced_table;
	CC_HashTable* freed_table;

	void* (*malloc)(size_t size);
	void* (*calloc)(size_t count, size_t size);
	void (*free)(void* ptr);
} mm_data;

typedef struct heap_chunk_s
{
	byte* start;
	size_t size;
	size_t user_size;
} heap_chunk;

static MemoryManager ops = { 0 };
static mm_data mm = { 0 };

static int ptrcmp(const void* ptr1, const void* ptr2)
{
	if (ptr1 == ptr2) { return 0; }
	if (ptr1 > ptr2) 
	{ 
		return 1; 
	}
	else 
	{
		return -1;
	}
}

static size_t GetNextAlignedSize(size_t size, size_t alignment)
{
	size_t alignment_in_bytes = alignment / 8;

	if ((size % alignment_in_bytes) != 0)
	{
		size_t mul_aligned_bytes = (size / alignment_in_bytes) + 1;
		size = mul_aligned_bytes * alignment_in_bytes;
	}
	return size;
}

static heap_chunk* mm_internal_malloc(size_t size)
{
	if (!size) { return NULL; }
	if ((mm.alloced_size + size) > mm.size) { return NULL; }

	heap_chunk* result = NULL;
	size_t aligned_size = GetNextAlignedSize(size, mm.alignment);

	CC_Array* array;
	if (cc_hashtable_get_keys(mm.freed_table, &array) == CC_OK)
	{
		const void* const* keys = cc_array_get_buffer(array);
		size_t num_keys = cc_array_size(array);

		heap_chunk* chunk;
		int chunk_index = -1;
		size_t aux_size = -1;
		for (size_t i = 0; i < num_keys; i++)
		{
			cc_hashtable_get(mm.freed_table, keys[i], &chunk);
			if (chunk->size >= aligned_size && chunk->size < aux_size)
			{
				chunk_index = i;
				aux_size = chunk->size;
			}
		}

		if (chunk_index >= 0)
		{
			cc_hashtable_remove(mm.freed_table, keys[chunk_index], &chunk);
			if (chunk->size == aligned_size)
			{
				result = chunk;
				chunk->user_size = size;
				assert(chunk->start >= mm.start && (chunk->start + chunk->size) <= mm.end);
				cc_hashtable_add(mm.alloced_table, chunk->start, chunk);
			}
			else
			{
				heap_chunk* new_chunk = (heap_chunk*)mm.malloc(sizeof(heap_chunk));
				new_chunk->start = chunk->start;
				new_chunk->size = aligned_size;
				new_chunk->user_size = size;

				result = new_chunk;

				chunk->start = new_chunk->start + new_chunk->size;
				chunk->size -= new_chunk->size;
				chunk->user_size = 0;
				assert(new_chunk->start >= mm.start && (new_chunk->start + new_chunk->size) <= mm.end);
				assert(chunk->start >= mm.start && (chunk->start + chunk->size) <= mm.end);
				assert(new_chunk->start < chunk->start && (new_chunk->start + new_chunk->size) == chunk->start);
				assert(new_chunk->start < mm.end);
				assert(chunk->start < mm.end);
				cc_hashtable_add(mm.alloced_table, new_chunk->start, new_chunk);
				cc_hashtable_add(mm.freed_table, chunk->start, chunk);
			}
			mm.alloced_size += aligned_size;
			assert(mm.alloced_size <= mm.size);
		}

		cc_array_destroy(array);
	}

	return result;
}

static void* mm_malloc(size_t size)
{
	heap_chunk* chunk = mm_internal_malloc(size);
	if (chunk)
	{
		return chunk->start;
	}
	return NULL;
}

static void* mm_calloc(size_t count, size_t size) 
{
	heap_chunk* chunk = mm_internal_malloc(size * count);
	if (chunk)
	{
		memset(chunk->start, 0, chunk->size);
		return chunk->start;
	}
	return NULL;
}

static void mm_free(void* ptr)
{
	if (!ptr) { return; }

	heap_chunk* chunk;
	if (cc_hashtable_remove(mm.alloced_table, ptr, &chunk) == CC_OK)
	{
		size_t original_size = chunk->size;

		heap_chunk* next_chunk = NULL;
		heap_chunk* previous_chunk = NULL;
		CC_Array* array;
		byte* aux_ptr = 0;
		if (cc_hashtable_get_keys(mm.freed_table, &array) == CC_OK)
		{
			const void* const* keys = cc_array_get_buffer(array);
			size_t num_keys = cc_array_size(array);

			for (size_t i = 0; i < num_keys; i++)
			{
				if (keys[i] < chunk->start && keys[i] > aux_ptr)
				{
					aux_ptr = keys[i];
				}

				if ((chunk->start + chunk->size) == keys[i])
				{
					cc_hashtable_remove(mm.freed_table, keys[i], &next_chunk);
				}
			}

			if (aux_ptr)
			{
				cc_hashtable_get(mm.freed_table, aux_ptr, &previous_chunk);
				if ((previous_chunk->start + previous_chunk->size) == chunk->start)
				{
					cc_hashtable_remove(mm.freed_table, aux_ptr, &previous_chunk);
				}
				else
				{
					previous_chunk = NULL;
				}
			}

			if (previous_chunk)
			{
				chunk->start = previous_chunk->start;
				chunk->size += previous_chunk->size;
				mm.free(previous_chunk);
			}

			if (next_chunk)
			{
				chunk->size += next_chunk->size;
				mm.free(next_chunk);
			}

			chunk->user_size = 0;

			cc_array_destroy(array);
		}
		mm.alloced_size -= original_size;

		assert(mm.alloced_size >= 0);

		cc_hashtable_add(mm.freed_table, chunk->start, chunk);
	}	
}

static void mm_status()
{

	printf("\033[1m\033[34m");
	printf("----------------------------------------------------------------------\n");
	printf("\x1B[0m");

	printf(" Custom Memory Manager Status:\n");
	printf(" Memory Usage: %zu/%zu bytes\n\n", mm.alloced_size, mm.size);

	CC_Array* array;
	if (cc_hashtable_get_keys(mm.alloced_table, &array) == CC_OK)
	{
		const void* const* keys = cc_array_get_buffer(array);
		size_t num_keys = cc_array_size(array);



		heap_chunk* chunk;
		for (size_t i = 0; i < num_keys; i++)
		{
			cc_hashtable_get(mm.alloced_table, keys[i], &chunk);

			printf("\033[1m\033[33m");
			printf("- [Warning]");
			printf("\x1B[0m");

			printf(" Allocated %zu bytes waiting to be freed (addres = 0x%p)\n", chunk->user_size, chunk->start);
		}

		cc_array_destroy(array);
	}
	else
	{
		printf("\033[1m\033[32m");
		printf("- [Succes]");
		printf("\x1B[0m");

		printf(" Everything seems OK\n");
	}

	printf("\033[1m\033[34m");
	printf("----------------------------------------------------------------------\n");
	printf("\x1B[0m\n");
	
}

static void mm_destroy()
{
	CC_Array* array;
	if (cc_hashtable_get_keys(mm.alloced_table, &array) == CC_OK)
	{
		const void* const* keys = cc_array_get_buffer(array);
		size_t num_keys = cc_array_size(array);

		printf("Non freed pointers\n");

		heap_chunk* chunk;
		for (size_t i = 0; i < num_keys; i++) 
		{
			cc_hashtable_remove(mm.alloced_table, keys[i], &chunk);
			assert(chunk->start >= mm.start && (chunk->start + chunk->size) <= mm.end);
			printf("Memory leak at location 0x%p with size %zu\n", chunk->start, chunk->size);
			mm.free(chunk);
		}

		cc_array_destroy(array);
	}

	if (cc_hashtable_get_keys(mm.freed_table, &array) == CC_OK)
	{
		const void* const* keys = cc_array_get_buffer(array);
		size_t num_keys = cc_array_size(array);

		printf("Freed pointers\n");

		heap_chunk* chunk;
		for (size_t i = 0; i < num_keys; i++)
		{
			cc_hashtable_remove(mm.freed_table, keys[i], &chunk);
			assert(chunk->start >= mm.start && (chunk->start + chunk->size) <= mm.end);
			printf("Memory freed at location 0x%p with size %zu\n", chunk->start, chunk->size);
			mm.free(chunk);
		}

		cc_array_destroy(array);
	}

	cc_hashtable_destroy(mm.alloced_table);
	cc_hashtable_destroy(mm.freed_table);

	mm.free(mm.start);

	ops.malloc = NULL;
	ops.calloc = NULL;
	ops.free = NULL;
	ops.status = NULL;
	ops.destroy = NULL;
}

void MM_Cfg_Init(MM_Cfg* cfg)
{
	if (!cfg) { return; }

	cfg->size = 0;
	cfg->alignment = 32;
	cfg->malloc = malloc;
	cfg->calloc = calloc;
	cfg->free = free;
}

enum MM_Status MemoryManager_Init(const MM_Cfg* cfg)
{
	if (!cfg) { return MM_INVALID_ARGUMENTS; }
	if (!cfg->size) { return MM_INVALIDE_CFG; }
	if (!cfg->malloc) { return MM_INVALIDE_CFG; }
	if (!cfg->calloc) { return MM_INVALIDE_CFG; }
	if (!cfg->free) { return MM_INVALIDE_CFG; }

	mm.size = GetNextAlignedSize(cfg->size, cfg->alignment);
	mm.alignment = cfg->alignment;
	mm.malloc = cfg->malloc;
	mm.calloc = cfg->calloc;
	mm.free = cfg->free;

	mm.start = mm.calloc(mm.size, 1);
	mm.end = mm.start + mm.size;
	mm.alloced_size = 0;

	CC_HashTableConf alloced_cfg;
	cc_hashtable_conf_init(&alloced_cfg);

	alloced_cfg.key_length = sizeof(void*);
	alloced_cfg.hash = POINTER_HASH;
	alloced_cfg.key_compare = ptrcmp;
	alloced_cfg.load_factor = 1.0f;
	alloced_cfg.initial_capacity = 100;

	cc_hashtable_new_conf(&alloced_cfg, &mm.alloced_table);

	CC_HashTableConf freed_cfg;
	cc_hashtable_conf_init(&freed_cfg);

	freed_cfg.key_length = sizeof(void*);
	freed_cfg.hash = POINTER_HASH;
	freed_cfg.key_compare = ptrcmp;
	freed_cfg.load_factor = 1.0f;
	freed_cfg.initial_capacity = 100;

	cc_hashtable_new_conf(&freed_cfg, &mm.freed_table);
	
	heap_chunk* chunk = mm.malloc(sizeof(heap_chunk));
	chunk->start = mm.start;
	chunk->size = mm.size;
	chunk->user_size = 0;
		
	cc_hashtable_add(mm.freed_table, chunk->start, chunk);

	ops.malloc = mm_malloc;
	ops.calloc = mm_calloc;
	ops.free = mm_free;
	ops.status = mm_status;
	ops.destroy = mm_destroy;
	
	return MM_OK;
}

MemoryManager* MemoryManager_Instance()
{
	return &ops;
}