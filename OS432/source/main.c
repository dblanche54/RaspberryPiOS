/* Main C method, jumped to from init.s */

#include "memory.h"
#include "process.h"

int main(void)
{
	struct FrameBuferDescription* bufDesc = (struct FrameBuferDescription*) 
		InitialiseFrameBuffer(1024, 768, 16);
	SetGraphicsAddress(bufDesc);
	
	memory_init();
	processes_init();
	
	return 0;
}
