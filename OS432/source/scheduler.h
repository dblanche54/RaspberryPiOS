/**
 * This file contains the scheduling and context switching facility.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2014
 */

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

/* Flag to indicate that schedule has not been called at all yet. */
int SCHEDULE_FIRST_FLAG;

/**
 * Schedule and switch to an active process.
 * Note: this routine does not return. If a process blocks itself, then calls
 * schedule(), execution may at a later point resume after the schedule() call.
 * However, this is a result of another process unblocking the blocked process,
 * and the scheduler scheduling it.
 */
void schedule();

#endif
