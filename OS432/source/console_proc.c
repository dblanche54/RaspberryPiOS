/**
 * The function executed by the console process.
 * The console processes has queues of operations that it needs to perform.
 * Operations are either input (keyboard) or output (monitor).
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#include "console_proc.h"
#include "io_config.h"
#include "print.h"
#include "user_syscalls.h"

/**
 * Move the contents of the screen up by a single line.
 */
void move_screen_up()
{
	
}

int console_proc()
{
	int cursorX = 0;
	int cursorY = 0;
	int status;
	char[MAX_IO_STRING_SIZE] buffer;
	
	unsigned int pid;
	struct io_request* data;
	unsigned int size;
	
	while(1)
	{
		size = MAX_IO_STRING_SIZE;
		status = osc_receive(&pid, (void*) data, &size);
		
	}
	
	return 0;
}
