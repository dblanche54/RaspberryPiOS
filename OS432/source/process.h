/**
 * This file contains the description of a process, as well as the system
 * process management routines and structures.
 * 
 * Author: Omar Zarifi
 * Date: March 11, 2014
 */

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "ipc_facility.h"
#include "memory.h"

/* Default heap and stack sizes for a user process. */
#define USER_HEAP_SIZE 65536
#define USER_STACK_SIZE 65536

/* Process state. */
enum process_state
{
	ACTIVE,
	BLOCKED,
	BLOCKED_SEND,
	BLOCKED_RECEIVE
};

struct process;

/* A node for a list of processes. */
struct process_node
{
	struct process* proc;
	struct process_node* next;
};

/* A list of processes. */
struct process_list
{
	struct process_node* head;
	struct process_node* tail;
};

/* A process descriptor. */
struct process
{
	/* PID. */
	unsigned int pid;
	/* PID of the parent. */
	unsigned int ppid;
	/* Pointer to the top of the process stack. */
	void* stack_pointer;
	/* Pointer to the next instruction to execute. */
	void* program_counter;
	/* Process heap. */
	heap process_heap;
	/* State of the process. */
	enum process_state state;
	/* List of children of this process. */
	struct process_list children;
	/* Queue of sent messages. */
	struct ipc_msg_list message_queue;
	/* Structure for the reply. */
	struct ipc_node reply;
};

/* The active process. */
struct process* current;

/* List of processes in the system. */
struct process_list processes;

/**
 * Initialize the process sytem.
 */
void processes_init();

/**
 * Return a pointer to a process structure given its pid.
 */
struct process* get_by_pid(unsigned int pid);

#endif
