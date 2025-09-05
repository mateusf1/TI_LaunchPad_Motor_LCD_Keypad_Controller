/*
 * keypad_4x4.c
 *
 * Init and read 4x4 keypad inputs
 *
 * By: Mateus A. Fernandes A. (GitHum: mateusf1)
 */

#include <msp430.h>
#include "keypad_4x4.h"

// USING PORT P3

unsigned char key_arr[] = {'1','2','3','A',
                           '4','5','6','B',
                           '7','8','9','C',
                           '*','0','#','D'};
// Init keypad ports
void keypad_init(void){
    //-- Configure GPIO ----------------------------------------------
    P3DIR = 0x0F; // Set P3.0 to 3.3 Output, Set P3.4 to 3.7 Input
    P3REN = 0xFF; // Set P3.0 to 3.7 enable pull up/down
    P3OUT = 0xF0; // Set P3.0 to 3.3 output to 0; Select P3.4 to 3.7 as pull-up inputs

    PM5CTL0 &= ~LOCKLPM5;       // Turn on GPIO
}

// Read keys from keypad
// If key is pressed, return respective char. Otherwise, return 0.
unsigned char get_key(void){
    unsigned int r,key = 0;

    KEYPAD_ROW = 0xF0;
    if(KEYPAD_COL == 0xF0){
        return 0; /* no key pressed */
    }

    /* Else: key is presses */
    for(r=0; r<4 ; r++){
        KEYPAD_ROW = ~(0x01<<r);    // Scan for a Key by sending '0' on KEYPAD_ROW
        if(KEYPAD_COL == 0xF0){         // Skip row if all KEYPAD_COL bits are '1'
            key += 4;
            continue;
        }
        else if(KEYPAD_COL == 0xE0){    // Col 0
            key += 0;
        }
        else if(KEYPAD_COL == 0xD0){    // Col 1
            key += 1;
        }
        else if(KEYPAD_COL == 0xB0){    // Col 2
            key += 2;
        }
        else if(KEYPAD_COL == 0x70){    // Col 3
            key += 3;
        }
        else{                           // Error or key not presses
            return 0;
        }
        while(KEYPAD_COL != 0xF0);
        __delay_cycles(100000);           // wait ~0.1 sec for debouncing
        return key_arr[key];
    }
    return 0;  // Error or key not presses
 }


