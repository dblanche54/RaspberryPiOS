/* 
 * 432 Team A
 * Print Methods
 *
 */

#include "print.h"

void drawCharacter(int charVal, int x, int y)
{
	asm volatile("mov r0, #120\n\t"
		"mov r1, #50\n\t"
		"mov r2, #50\n\t"
		"bl DrawCharacter"
	   );
}

void drawString(void *string, int length, int x, int y)
{

}
