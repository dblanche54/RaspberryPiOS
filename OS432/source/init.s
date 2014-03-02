/* This code jumps to main */

.section .init
.globl _start
_start:

/*
* Branch to the main function defined in main.c.
*/

mov sp,#0x8000

b main
