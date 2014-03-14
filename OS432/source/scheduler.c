/**
 * This file contains the scheduling and context switching facility.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2014
 */

#include "process.h"
#include "scheduler.h"

void schedule()
{
	if(SCHEDULE_FIRST_FLAG == 0)
	{
		/* Choose the next process. */
		struct process_node* node = processes.head;
		while(node != NULL)
		{
			processes.head = node->next;
			processes.tail->next = node;
			processes.tail = node;
			node->next = NULL;
			
			if(node->proc->state == ACTIVE)
			{
				current = node->proc;
				node = NULL;
			}
		}
	}
	else
	{
		SCHEDULE_FIRST_FLAG = 0;
	}
	
	/* Restore context of current process. */
	asm volatile
	(
		"mov sp, %1\n\t"
		"mov pc, %2\n\t"
		:
		: current->stack_pointer, current->program_counter
	);
}
