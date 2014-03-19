/**
 * Function executed by the first process.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2013
 */

#include "print.h"
#include "tostring.h"

void master_process()
{
	unsigned int cpsr;
	char dog[32];
	
	/* The messages to be printed */
	char greetingMessage[] = "Welcome to our Operating System";
	char promptMessage[] = "Please enter a command: ";
	
	/* Printing opening message / prompt */
	DrawString(greetingMessage, 31, 0, 0);
	DrawString(promptMessage, 24, 0, 16);
	
	asm volatile
	(
		"mrs %0, cpsr \n"
		: "=r" (cpsr)
	);
	toBinString((void*) cpsr, dog);
	DrawString(dog, 32, 0, 32);
	
	while(1)
	{
		
	}
}
