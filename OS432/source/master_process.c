/**
 * Function executed by the first process.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2013
 */

#include "print.h"
#include "tostring.h"

int dog = 0;

void master_process()
{
	char message[] = "Master Process";
	DrawString(message, 14, 0, dog);
	dog = dog + 16;
	while(1)
	{
		
	}
}
