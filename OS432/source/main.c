/* Main C method, jumped to from init.s */

#include "memory.h"
#include "process.h"
#include "interrupts.h"
#include "tostring.h"
#include "print.h"
#include "timer.h"
#include "int_handlers.h"

unsigned long long sys_time;

int main(void)
{
	int i;
	char hex[10];
	struct FrameBuferDescription* bufDesc = (struct FrameBuferDescription*) 
		InitialiseFrameBuffer(1024, 768, 16);
	SetGraphicsAddress(bufDesc);

	toHexString((void *)16, hex);
	DrawString(hex, 10, 200, 16);
	asm volatile
	(
		"mrs r0, cpsr \n"
		"mvn r1, #0x80 \n"
		"and r0, r0, r1 \n"
		"msr cpsr, r0 \n"
	);

	memory_init();
	idt_init();
	loadPreDivValue(10);
	enableTimerInterrupts();
	loadTimerValue(0xFFFFFFFF);
	enableTimer();
	sys_time = GetTimeStamp(); 

	for(i = 0; i < 1000000; i++);
	toHexString((void *)16, hex);
	DrawString(hex, 10, 200, 0);
	processes_init();

	return 0;
}
