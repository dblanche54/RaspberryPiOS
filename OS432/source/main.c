/* Main C method, jumped to from init.s */

#include "int_handlers.h"
#include "io_init.h"
#include "memory.h"
#include "process.h"

void main()
{
	input_init();
	output_init();
	memory_init();
	idt_init();
	processes_init();
}
