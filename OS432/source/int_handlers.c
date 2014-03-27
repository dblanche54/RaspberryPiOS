/**
 * This file contains interrupt handler functions.
 * 
 * Author: Omar Zarifi
 * Date: March 19, 2014
 */

#include "cpu_context.h"
#include "memcpy.h"
#include "memory.h"
#include "print.h"
#include "process.h"
#include "tostring.h"
#include "interrupts.h"
#include "timer.h"
#include "scheduler.h"

void idt_init()
{
	unsigned int* address = (unsigned int*) 0x802C;
	int i = 0;
	for(i = 0; i < 7; i++)
	{
		address[i] = 0x8048 + i * 4;
	}
	
	memcpy((void*) ((unsigned int) 0), (void*) (KERNEL_STACK_START + 12),
		8 * 7);
}

void internal_svc_handler()
{
}

void svc_handler()
{
}

void irq_handler()
{
	save_context();
	current->program_counter = (void*) (((unsigned int) current->program_counter) - 4);
	disableTimer();
	ackTimerInterrupt();
	enableTimer();
	schedule();
}
