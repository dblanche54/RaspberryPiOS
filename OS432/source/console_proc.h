/**
 * The function executed by the console process.
 * The console processes has queues of operations that it needs to perform.
 * Operations are either input (keyboard) or output (monitor).
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#ifndef _CONSOLE_PROC_H_
#define _CONSOLE_PROC_H_

/* Request type; either input or output. */
enum io_request_type
{
	INPUT,
	OUTPUT,
	LINE_BREAK
};

/* A structure to encode a request for service from the console. */
struct io_request
{
	enum io_request_type type;
	void* address;
	unsigned int size;
};

int console_proc();

#endif
