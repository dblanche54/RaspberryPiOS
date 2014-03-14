/**
 * This file contains the process-related routines.
 * 
 * Author: Omar Zarifi
 * Date: March 11, 2014
 */

#include "memory.h"
#include "process.h"
#include "schedule.h"

/* Flag to indicate that schedule has not been called at all yet. */
int SCHEDULE_FIRST_FLAG;

/* Note: memory must be initialized before processes.
 * Processes can be initialized last. */
void processes_init()
{
	struct process_node* node;
	
	/* Create the master process. */
	struct process* master = (struct process*) kmalloc(sizeof(struct process));
	master->pid = 1;
	master->ppid = 0;
	master->program_counter = KERNEL_STACK_START + 8;
	master->process_heap.address = kmalloc(USER_HEAP_SIZE + USER_STACK_SIZE);
	master->process_heap.size = USER_HEAP_SIZE;
	master->stack_pointer = (void*) (((char*) master->process_heap.address)
		+ USER_HEAP_SIZE + USER_STACK_SIZE);
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
