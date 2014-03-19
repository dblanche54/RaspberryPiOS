/**
 * This file contains the process-related routines.
 * 
 * Author: Omar Zarifi
 * Date: March 11, 2014
 */

#include "leds.h"
#include "memory.h"
#include "process.h"
#include "scheduler.h"
#include "print.h"
#include "tostring.h"

#define NULL ((void*) 0)

int debug = 0;

/* Note: memory must be initialized before processes.
 * Processes can be initialized last. */
void processes_init()
{
	struct process_node* node;
	unsigned int cpsr;
	char hex[10];
	char dog[32];
	
	/* Create the master process. */
	struct process* master = (struct process*) kmalloc(sizeof(struct process));
	toHexString((void*) master, hex);
	DrawString(hex, 10, 50, 50);
	master->pid = 1;
	master->ppid = 0;
	master->program_counter = (void*) ((unsigned int) (0x8008));
	master->process_heap.address = kmalloc(USER_HEAP_SIZE + USER_STACK_SIZE);
	master->process_heap.size = USER_HEAP_SIZE;
	master->stack_pointer = (void*) (((char*) master->process_heap.address)
		+ USER_HEAP_SIZE + USER_STACK_SIZE - 15 * 4);
	asm volatile
	(
		"mrs %0, cpsr \n"
		//"mov r1, #0xF \n"
		//"mvn r1, r1 \n"
		//"and %0, r0, r1 \n"
		: "=r" (cpsr)
	);
	*((unsigned int*) master->stack_pointer) = cpsr;
	toBinString((void*) cpsr, dog);
	DrawString(dog, 32, 50, 82);
	toHexString(master->stack_pointer, hex);
	DrawString(hex, 10, 50, 66);
	toHexString(master->process_heap.address, hex);
	DrawString(hex, 10, 50, 98);
	toHexString((unsigned int) master->program_counter, hex);
	DrawString(hex, 10, 50, 114);
	master->process_heap.next = NULL;
	master->state = ACTIVE;
	master->children.head = NULL;
	master->children.tail = NULL;
	master->message_queue.head = NULL;
	master->message_queue.tail = NULL;
	/* Note that the reply field does not need initialization. */
	
	/* Initialize the system structures that keep track of processes. */
	current = master;
	node = (struct process_node*) kmalloc(sizeof(struct process_node));
	node->proc = master;
	node->next = NULL;
	processes.head = node;
	processes.tail = node;
	
	toHexString((unsigned int) master->program_counter, hex);
	DrawString(hex, 10, 50, 130);
	
	/* The master process will now take control. */
	SCHEDULE_FIRST_FLAG = 1;
	schedule();
}

struct process* get_by_pid(unsigned int pid)
{
	struct process_node* node = processes.head;
	while(node != NULL || node->proc->pid != pid)
	{
		node = node->next;
	}
	if(node == NULL)
	{
		return NULL;
	}
	else
	{
		return node->proc;
	}
}
