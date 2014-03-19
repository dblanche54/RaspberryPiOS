/* This code jumps to main */

.section .init
.globl _start
_start:

/*
* Branch to the main function defined in main.c.
*/

mov sp, #0x8000
b main
mov r0, #16
mov r1, #1
bl SetGpioFunction
mov r0, #16
mov r1, #0
bl SetGpio
b master_process
