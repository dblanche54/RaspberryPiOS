/* This code jumps to main */

.section .init
.globl _start
_start:

/*
* Branch to the main function defined in main.c.
*/

mov sp, #0x8000			/* 0x8000 */
b main					/* 0x8004 */
b master_process		/* 0x8008 */
mov r0, r0				/* 0x800C */
