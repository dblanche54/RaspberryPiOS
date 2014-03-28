/**
 * This file contains interrupt handler functions.
 * 
 * Author: Omar Zarifi
 * Date: March 19, 2014
 */

#include "cpu_context.h"
#include "interrupts.h"
#include "memcpy.h"
#include "memory.h"
#include "process.h"
#include "syscalls.h"
#include "timer.h"

#define NULL ((void*) 0)

void idt_init()
{
	unsigned int* address = (unsigned int*) 0x802C;
	int i = 0;
	for(i = 0; i < 7; i++)
	{
		address[i] = 0x8048 + i * 4;
	}
	
	memcpy((void*) ((unsigned int) 0), (void*) (KERNEL_STACK_START + 12),
		8 * 7 + 4);
}

void svc_handler()
{
	save_context();
	
	unsigned int* args = (unsigned int*)
		(((unsigned int) current->stack_pointer) + 32);
	unsigned long long ret = syscall_functions[args[5]](args[4], args[3],
		args[2], args[1], args[0]);
	/* Note: we put the more significant half into r0 and less significant half
	 * into r1. */
	unsigned int top = (unsigned int) (ret / 0x100000000ull);
	unsigned int bottom = (unsigned int) (ret % 0x100000000ull);
	args[4] = top;
	args[5] = bottom;
	
	restore_context();
}

void irq_handler()
{
	save_context();
	
	disableTimer();
	
	current->program_counter =
		(void*) (((unsigned int) current->program_counter) - 4);
	
	/* Wake up any sleeping processes that should be done sleeping. */
	unsigned long long current_time = GetTimeStamp();
	struct process_node* prev = NULL;
	struct process_node* node = sleeping.head;
	while(node != NULL)
	{
		if(node->proc->wakeup_time <= current_time)
		{
			struct process_node* temp;
			node->proc->state = ACTIVE;
			
			/* Remove the node from the sleeping list. */
			if(prev == NULL)
			{
				sleeping.head = node->next;
			}
			else
			{
				prev->next = node->next;
			}
			if(node->next == NULL)
			{
				sleeping.tail = prev;
			}
			
			temp = node;
			node = node->next;
			kfree(temp);
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
	
	/* Set up the timer once again. */
	ackTimerInterrupt();
	enableTimer();
	
	schedule();
}
