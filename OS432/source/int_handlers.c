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

extern unsigned long long sys_time;

void irq_handler()
{
	char message[] = "IN IRQ";
	char hex[10];
	unsigned int time;
	asm volatile
	(
		"mov sp, #0x8000 \n\t"
	);
	sys_time = GetTimeStamp() - sys_time;
	time = (unsigned int) sys_time % 0xFFFFFFFF;
	toHexString((void*) time, hex);
	DrawString(hex, 10, 200, 200);

	disableTimer();
	DrawString(message, 6, 150, 150);

	toHexString((void *)getTimerValue(), hex);
	DrawString(hex, 10, 175, 175);

	ackTimerInterrupt();	
	
	enableTimer();
}
