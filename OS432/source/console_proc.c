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
#include "memcpy.h"
#include "print.h"
#include "user_syscalls.h"

/* Where to start copying. */
#define START_COPY_ADDRESS (void*) \
	(((unsigned int) framebuffer) \
		+ H_RESOLUTION * REFRESH_LINE * V_CHAR * BITS_PER_PIXEL)
/* How much to clear. */
#define CLEAR_AMOUNT H_RESOLUTION * (V_SCREEN_CHARS - REFRESH_LINE) * V_CHAR \
	* BITS_PER_PIXEL / sizeof(unsigned int)
/* How much to copy. */
#define COPY_AMOUNT H_RESOLUTION * REFRESH_LINE * V_CHAR * BITS_PER_PIXEL

/**
 * Move the contents of the screen up.
 */
void move_screen_up()
{
	unsigned int* temp = (int*) START_COPY_ADDRESS;
	int i;
	
	memcpy(framebuffer, START_COPY_ADDRESS, COPY_AMOUNT);
	for(i = 0; i < CLEAR_AMOUNT; i++)
	{
		temp[i] = 0;
	}
}

int console_proc()
{
	unsigned int cursorX = 0;	/* In cells, not pixels. */
	unsigned int cursorY = 0;	/* In cells, not pixels. */
	unsigned int numCanPrint;
	unsigned int numPrinted;
	unsigned int status;
	char* string;
	
	unsigned int pid;
	struct io_request data;
	
	while(1)
	{
		size = sizeof(struct io_request);
		status = osc_receive(&pid, &data, &size);
		
		if(status == 0)
		{
			switch(data.type)
			{
				case INPUT:
					
					break;
				
				case OUTPUT:
				/* Let it fall through to OUTPUT_LN case. */
				
				case OUTPUT_LN:
					string = data.string;
					numPrinted = 0;
					
					while(data.size > 0)
					{
						numCanPrint = H_SCREEN_CHARS - cursorX;
						if(numCanPrint > data.size)
						{
							numPrinted = data.size;
						}
						else
						{
							numPrinted = numCanPrint;
						}
						
						DrawString(string, numPrinted, cursorX * H_CHAR,
							cursorY * H_CHAR);
						
						cursorX = cursorX + numPrinted;
						if(cursorX == H_SCREEN_CHARS)
						{
							cursorX = 0;
							cursorY = cursorY + 1;
							if(cursorY == V_SCREEN_CHARS)
							{
								move_screen_up();
								cursorY = REFRESH_LINE;
							}
						}
						
						data.size = data.size - numPrinted;
						string = string + numPrinted;
					}
					
					if(data.type == OUTPUT_LN)
					{
						if(cursorY == V_SCREEN_CHARS)
						{
							move_screen_up();
							cursorY = REFRESH_LINE;
						}
					}
					
					break;
			}
		}
	}
	
	return 0;
}
