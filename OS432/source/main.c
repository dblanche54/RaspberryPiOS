/* Main C method, jumped to from init.s */

#include "print.h"
#include "leds.h"
#include "timer.h"
#include "tostring.h"
#include "keyboard.h"

int main(void)
{
	/* The messages to be printed */
	char greetingMessage[] = "Welcome to our Operating System";
	char promptMessage[] = "Please enter a command: ";
	char letter;
	int x = 0;
	int y = 32;

	/* Preparing the screen to print */
	SetGraphicsAddress(InitialiseFrameBuffer(1024, 768, 16));

	/* Printing opening message / prompt */
	DrawString(greetingMessage, 31, 0, 0);
	DrawString(promptMessage, 24, 0, 16);

	/* Setting up the keyboard */
	while(UsbInitialise() != 0);

	/* Getting / printing keyboard input to screen */
	while(1)
	{
		KeyboardUpdate();
		letter = KeyboardGetChar();
		if(letter != 0 && letter >= 0 && letter <= 127)
		{
			if(letter == '\n')
			{
				x = 0;
				y += 16;
			}
			else
			{
				DrawCharacter(letter,x,y);
				x += 8;
			}
			if(x >= 1024)
			{
				x = 0;
				y += 16;
			}
			if(y >= 768)
			{
				break;
			}
		}
	}

	/* Infinite blinking */
	ledblink();

	return 0;
}
