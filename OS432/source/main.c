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
	int r;
	
	/* Preparing the screen to print */
	struct FrameBuferDescription *bufDesc = InitialiseFrameBuffer(1024, 768, 16);
	SetGraphicsAddress(bufDesc);


	/* Trying to communicate with a keyboard */
	ledon();
	UsbInitialise();
	
	r = KeyboardCount();

	while(r==0)
	{
		DrawString("No Keyboard Detected", 20, 0,0);
		UsbCheckForChange();
		r = KeyboardCount();
	}
	clearScreen(bufDesc);
	ledoff();

	/* Printing opening message / prompt */
	DrawString(greetingMessage, 31, 0, 0);
	DrawString(promptMessage, 24, 0, 16);
	
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
			else if(letter == '*')
			{
				break;
			}
			else if(letter == '-')
			{
				ledoff();
			}
			else if(letter == '+')
			{
				ledon();
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
				newRowOnScreen(bufDesc);
				x = 0;
				y -= 16;
			}
		}
	}

	return 0;
}
