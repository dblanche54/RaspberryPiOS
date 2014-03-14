/**
 * Prototypes for system calls available to be called by a user program.
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#ifndef _USER_SYSCALLS_H_
#define _USER_SYSCALLS_H_

/******************************************************************************
 * Memory management.
 *****************************************************************************/

/* Allocate a chunk of memory of the desired size (in bytes) and return a
 * pointer to the chunk. */
void* osc_malloc(unsigned int size);
/* Free a previously allocated chunk of memory. */
void osc_free(void* address);

/******************************************************************************
 * Inter-process communication.
 *****************************************************************************/

/* Send a message of (at most) the given size to the given process. Returns 0
 * on success, non-zero on failure.
 * This blocks until the receiver replies. */
int osc_send(unsigned int pid, void* msg, unsigned int size, void* reply,
	unsigned int* r_size);
/* Receive a message of (at most) the given size. When the call returns, pid
 * holds the sender PID, and size holds the actual message size. Returns 0 on
 * success, non-zero on failure.
 * Note that this call blocks until a message is sent by another process. */
int osc_receive(unsigned int* pid, void* msg, unsigned int* size);
/* Reply to a process that is waiting for a reply from this process. Returns 0
 * on success, non-zero on failure. */
int osc_reply(unsigned int pid, void* msg, unsigned int size);

/******************************************************************************
 * Process-related.
 *****************************************************************************/

/* Return the PID of the calling process. */
unsigned int osc_getpid();
/* Return the PID of the parent of the calling process. */
unsigned int osc_getppid();
/* Fork a new child process. On failure returns 0. To the new child returns 1.
 * To the parent returns the PID of the new child. */
unsigned int osc_fork();
/* Wait for the child with the given PID to exit. */
void osc_waitpid(unsigned int pid);
/* Terminate the calling process with the given exit code. */
void osc_exit(int ret);
/* Sleep for (at least) the given duration (in microseconds). */
void osc_sleep(unsigned int duration);
/* Voluntarily give up the processor. */
void osc_yield();

/******************************************************************************
 * Input/output.
 *****************************************************************************/

/* Print the given string at the cursor position. Size of the string must also
 * be provided. */
void osc_print_string(char* string, unsigned int size);
/* Get a string from the keyboard. Maximum size of the string must also be
 * provided. */
void osc_get_string(char* string, unsigned int size);

#endif
