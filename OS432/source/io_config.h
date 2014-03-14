/**
 * Input/output configuration.
 * Note: H - horizontal, V - vertical.
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#ifndef _IO_CONFIG_H_
#define _IO_CONFIG_H_

/* Output resolution. */
#define H_RESOLUTION 1280
#define V_RESOLUTION 720

/* Character size. */
#define H_CHAR 8
#define V_CHAR 16

/* Number of characters that can be printed on screen. */
#define H_SCREEN_CHARS (H_RESOLUTION / H_CHAR)
#define V_SCREEN_CHARS (V_RESOLUTION / V_CHAR)

/* Maximum size of an input/output string. */
#define MAX_IO_STRING_SIZE 256

#endif
