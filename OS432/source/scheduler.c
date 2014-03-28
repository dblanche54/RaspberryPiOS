/**
 * This file contains the scheduling and context switching facility.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2014
 */

#include "cpu_context.h"
#include "process.h"
#include "scheduler.h"

#define NULL ((void*) 0)

void schedule()
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
	
	restore_context();
}
