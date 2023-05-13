/**
 * @file adt_memory_node.h
 * @author Hector Ochando <ochandoca@esat-alumni.com>
 */

#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"

typedef struct adt_queue_s {
	struct adt_list_s* storage_;
	struct queue_ops_s* ops_;
} Queue;

struct queue_ops_s {
	s16 (*reset)(Queue *queue);
	s16 (*enqueue)(Queue *queue, void *data, u16 bytes);
	boolean (*isEmpty)(Queue *queue);
	boolean (*isFull)(Queue *queue);
	u16 (*capacity)(Queue *queue);
	s16 (*resize)(Queue *queue, u16 new_size);
	void* (*dequeue)(Queue *queue);
	u16 (*length)(Queue *queue);
	void* (*front)(Queue *queue);
	void* (*back)(Queue *queue);
	s16 (*concat)(Queue *queue, Queue *queue_src);
	s16 (*destroy)(Queue *queue);
	void (*print)(Queue *queue);
};

Queue* QUEUE_create(u16 size);

#endif //__ADT_QUEUE_H__