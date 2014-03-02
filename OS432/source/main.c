/* Main C method, jumped to from init.s */

#include "print.h"
#include "leds.h"
#include "timer.h"

int main(void)
{
	/* The messages to be printed */
	char greetingMessage[] = "Welcome to our Operating System";
	char promptMessage[] = "Please enter a command: ";

	/* Preparing the screen to print */
	SetGraphicsAddress(InitialiseFrameBuffer(1024,768,16));
	
	/* Printing to screen */
	DrawString(greetingMessage, 31, 0, 0);
	DrawString(promptMessage, 24, 0, 16);

	/* Infinite blinking */
	ledblink();

	return 0;
}
