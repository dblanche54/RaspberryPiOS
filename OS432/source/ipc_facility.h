/**
 * IPC facility data structures.
 * 
 * Author: Omar Zarifi
 * Date: March 11, 2014
 */

#ifndef _IPC_FACILITY_H_
#define _IPC_FACILITY_H_

/**
 * A node to represent a sent message.
 */
struct ipc_node
{
	void* data;
	unsigned int size;
	unsigned int sender;
	struct ipc_node* next;
};

/**
 * List of messages. Used as a queue.
 */
struct ipc_msg_list
{
	struct ipc_node* head;
	struct ipc_node* list;
};

#endif
