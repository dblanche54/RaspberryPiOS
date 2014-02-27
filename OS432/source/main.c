/* Main C method, jumped to from init.s */

#include "print.h"
#include "leds.h"
#include "timer.h"

int main(void)
{
	/* Preparing to print */
	SetGraphicsAddress(InitialiseFrameBuffer(1024,768,16));

	/* Printing prompt */
	DrawCharacter('W',0,0);
	DrawCharacter('e',8,0);
	DrawCharacter('l',16,0);
	DrawCharacter('c',24,0);
	DrawCharacter('o',32,0);
	DrawCharacter('m',40,0);
	DrawCharacter('e',48,0);
	DrawCharacter(' ',56,0);
	DrawCharacter('t',64,0);
	DrawCharacter('o',72,0);
	DrawCharacter(' ',80,0);
	DrawCharacter('o',88,0);
	DrawCharacter('u',96,0);
	DrawCharacter('r',104,0);
	DrawCharacter(' ',112,0);
	DrawCharacter('O',120,0);
	DrawCharacter('S',128,0);

        DrawCharacter('P',0,16); 
        DrawCharacter('l',8,16); 
        DrawCharacter('e',16,16); 
        DrawCharacter('a',24,16);
        DrawCharacter('s',32,16);
        DrawCharacter('e',40,16);
        DrawCharacter(' ',48,16);
        DrawCharacter('e',56,16);
        DrawCharacter('n',64,16);
        DrawCharacter('t',72,16);
        DrawCharacter('e',80,16);
        DrawCharacter('r',88,16);
        DrawCharacter(' ',96,16);
        DrawCharacter('a',104,16);
        DrawCharacter(' ',112,16);
        DrawCharacter('c',120,16);
        DrawCharacter('o',128,16);
	DrawCharacter('m',136,16);
	DrawCharacter('m',144,16);
	DrawCharacter('a',152,16);
	DrawCharacter('n',160,16);
	DrawCharacter('d',168,16);
	DrawCharacter(':',176,16);
	DrawCharacter(' ',184,16);

	/* Infinite blinking */
	ledblink();

	return 0;
}
