-------------------------------------------------------------------------------
Chris Ross (Wednesday Feb 26th):
The pi successfully boots and prints a command prompt to the screen. The LED
functions, the print functions, and the wait function from the baking pi
tutorials can all be called from a C program at this point.

To get the toolchain you need to be able to compile the OS use the following
3 commands:

1) wget http://www.cl.cam.ac.uk/freshers/raspberrypi/tutorials/os/downloads/arm-none-eabi.tar.bz2

2) tar xjvf arm-none-eabi.tar.bz2

3) export PATH=$PATH:$HOME/arm-2008q3/bin   
-------------------------------------------------------------------------------
Chris Ross (Tuesday March 11th)
The pi attempts to communicate with a USB keyboard. If it fails it prints that
no keyboard was detected, and most likely has to be restarted. If it is
successful in communicating with a keyboard it prints the opening message and
accepts input. Pressing the '*' character will end input. Pressing '+' will
turn the led on. Pressing '-' will turn the led off. The screen will move up
if it fills up (slow, should be optimized). The keyboard driver is garbage and
should be rewritten if we have time, we are currently using the one from the
baking pi tutorials.  
