/* Main C method, jumped to from init.s */

#include "memory.h"
#include "process.h"
#include "interrupts.h"
#include "tostring.h"
#include "print.h"
#include "timer.h"
#include "int_handlers.h"

int main(void)
{
	bufDesc = (struct FrameBuferDescription*) 
		InitialiseFrameBuffer(1024, 768, 16);
	SetGraphicsAddress(bufDesc);

	memory_init();
	idt_init();
	loadPreDivValue(100);
	enableTimerInterrupts();
	loadTimerValue(0xFFFFFFFF);
	enableTimer();

	processes_init();

	return 0;
}
