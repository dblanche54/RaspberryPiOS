/**
 * This file contains the kernel memory management facility.
 * 
 * Author: Omar Zarifi
 * Date: March 7, 2014
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

/* Starting address and size of the kernel heap region. */
#define KERNEL_HEAP_START 16777216
#define KERNEL_HEAP_SIZE 268435456
/* Starting address of the kernel stack. */
#define KERNEL_STACK_START 32768

/**
 * A heap node is a chunk of free memory. Heap nodes are structured as a linked
 * list (kept sorted for efficiency).
 */
struct heap_node
{
	void* address;
	unsigned int size;
	struct heap_node* next;
};

/**
 * A heap structure. A heap is simply a free list.
 */
typedef struct heap_node heap;

/**
 * The kernel heap. Must be initalized.
 */
heap kernel_heap;

/**
 * The kernel stack pointer.
 */
void* kernel_stack;

/**
 * Allocate a chunk of memory in the kernel heap of the given size.
 */
void* kmalloc(unsigned int size);

/**
 * Deallocate a previously allocated chunk of memory (through kmalloc).
 */
void kfree(void* address);

/**
 * Allocate a chunk of memory in the given heap of the given size.
 */
void* memory_allocator(heap* h, unsigned int size);

/**
 * Deallocate a chunk of memory in the given heap.
 */
void memory_deallocator(heap* h, void* address);

/**
 * Initialize the kernel heap.
 */
void memory_init();

#ifdef _DEBUG_

struct debug_heap_info
{
	unsigned int number_of_nodes;
	void* starting_address;
	unsigned int starting_size;
};

/**
 * Return kernel heap info.
 */
struct debug_heap_info get_kernel_info();

#endif

#endif
