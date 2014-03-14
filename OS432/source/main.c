/* Main C method, jumped to from init.s */

#include "memory.h"
#include "processes.h"

int main(void)
{
	memory_init();
	processes_init();
	
	return 0;
}
