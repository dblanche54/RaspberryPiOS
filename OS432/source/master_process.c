/**
 * Function executed by the first process.
 */

#include "tostring.h"
#include "user_syscalls.h"

#define NULL ((void*) 0)

char welcomemsg[] = "Welcome to our OS";
char prompt[] = "Please enter a command: ";
char printcmd[] = "print";
char blinkcmd[] = "blink";
char factcmd[] = "fact";
char invalidcmd[] = "*** Not a valid command ***";
char command[33];

int factorialfunc(int i)
{
	if(i <= 1)
	{
		return 1;
	}
	return i * factorialfunc(i - 1);
}

unsigned int factorialprocess(void)
{
	char out[12];
	int i = factorialfunc(10);
	int numchar = toDecimalString(i, out);
	osc_print_line(out, numchar);
	while(1);
	return 0;
}

unsigned int printled(void)
{
	osc_print_line(printcmd, 5);
	while(1);
	return 0;
}

unsigned int blinkled(void)
{
	osc_print_line(blinkcmd, 5);
	while(1);
	return 0;
}

int strcmp(const char* string1, const char* string2)
{
	while(*string1 && (*string1==*string2))
	{
		string1++;
		string2++;
    	}
	return *(const unsigned char*)string1-*(const unsigned char*)string2;
}

void master_process()
{
	int *maxsize;
	*maxsize = 32;
	osc_print_line(welcomemsg, 17);

	while(1)
	{
		osc_print_line(prompt, 24);
		osc_get_string(command, maxsize);
		if(strcmp(command, blinkcmd) == 0)
		{
			internal_create_process(blinkled, 0, 0, 0, 0);
		}
		else if(strcmp(command, factcmd) == 0)
		{
			internal_create_process(factorialprocess, 0, 0, 0, 0);
		}
		else
		{
			osc_print_line(invalidcmd, 27);
		}
	}
}
