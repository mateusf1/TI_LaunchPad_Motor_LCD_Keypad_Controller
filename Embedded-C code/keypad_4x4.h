/*
 * keypad_4x4.h
 *
 * Init and read 4x4 keypad inputs
 */

#ifndef KEYPAD_4X4_H_
#define KEYPAD_4X4_H_

// Declare #defined MACROS
#define KEYPAD_ROW P3OUT
#define KEYPAD_COL (P3IN  & 0xF0)

// Declare the functions in the header:
void keypad_init(void);
unsigned char get_key(void);

#endif /* KEYPAD_4X4_H_ */
