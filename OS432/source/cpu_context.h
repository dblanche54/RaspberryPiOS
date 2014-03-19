/**
 * This file contains the context saving and restoring functionality.
 * 
 * Author: Omar Zarifi
 * Date: March 17, 2014
 */

#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include "memory.h"
#include "process.h"

/**
 * Routine to save the context to the process structure of the current process.
 * The routine is defined as a macro because we don't want to modify stacks
 * with function calls.
 * At the end of this call, the top of the stack of the current process will
 * contain lr, r0-r12, SPSR (in reverse order). Moreover, its updated stack
 * pointer and return address will be saved on the process structure.
 * Note: IRQ/FIQ handler must substract 4 from the saved program counter after
 * calling this routine.
 */
#define save_context() \
	asm volatile \
	( \
		"mov sp, %0 \n" \
		"push {r10-r12} \n" \
		"mov r10, #0x1F \n" \
		"mrs r11, cpsr \n" \
		"and r12, r11, r10 \n" \
		"mvn r10, r10 \n" \
		"orr r12, r12, r10 \n" \
		"mvn r10, r10 \n" \
		"orr r11, r11, r10 \n" \
		"msr cpsr, r11 \n" \
		"push {lr} \n" \
		"push {r0-r9} \n" \
		"mov r0, sp \n" \
		"and r11, r11, r12 \n" \
		"msr cpsr, r11 \n" \
		"pop {r1-r3} \n" \
		"mrs r4, spsr \n" \
		"mov r5, sp \n" \
		"mov sp, r0 \n" \
		"push {r1-r4} \n" \
		"mov r0, sp \n" \
		"mov r1, lr \n" \
		"mov sp, r5 \n" \
		"mov %1, r0 \n" \
		"mov %2, r1 \n" \
		: \
		: "i" (KERNEL_STACK_START), "X" (current->stack_pointer), \
			"X" (current->program_counter) \
	);

/**
 * Routine to restore the context of the current process.
 * The routine is defined as a macro because we don't want to modify stacks
 * with function calls.
 */
#define restore_context() \
	asm volatile \
	( \
		"mov lr, %0 \n" \
		"mov r0, sp \n" \
		"mov r10, #0x1F \n" \
		"mrs r11, cpsr \n" \
		"mov r12, r11 \n" \
		"orr r11, r11, r10 \n" \
		"msr cpsr, r11 \n" \
		"mov sp, r0 \n" \
		"mov r1, %1 \n" \
		"mov sp, r1 \n" \
		"pop {r5} \n" \
		"pop {r6-r9} \n" \
		"mov r1, sp \n" \
		"mov sp, r0 \n" \
		"push {r6-r9} \n" \
		"push {r5} \n" \
		"mov r9, sp \n" \
		"mov sp, r1 \n" \
		"pop {r0-r8} \n" \
		"pop {lr} \n" \
		"and r11, r11, r12 \n" \
		"msr cpsr, r11 \n" \
		"mov sp, r9 \n" \
		"pop {r9} \n" \
		"msr spsr, r9 \n" \
		"pop {r9-r12} \n" \
		"movs pc, lr \n" \
		: \
		: "X" (current->program_counter), "X" (current->stack_pointer) \
	);

#endif
