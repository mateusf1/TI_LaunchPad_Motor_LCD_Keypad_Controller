#include <msp430.h>
#include <stdio.h>
#include "LiquidCrystal_I2C.h"
#include "keypad_4x4.h"
#include "pwm.h"

void reset_LCD(void);

/**
 * main.c
 */
void main(void){
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // INIT & SETUP //

    /* keypad */
    unsigned char key_val = 0;
    keypad_init();

    /* I2C & LCD */
    I2C_init(0x27); // 0x27 signifies the slave address (address of the LCD with the I/O expander).
    LCD_Setup();
    reset_LCD();

    /* PWM signal (for motor) */
    pwm_init();


    /* Other Vars */
    unsigned short speed = 0;


    // MAIN LOOP //
    while(1){
        while((key_val = get_key())==0);          //Wait until a key Pressed

        if(speed == 0){
            reset_LCD();
        }

        if(key_val >= '0' && key_val <= '9'){ /* Enter digits  */
            LCD_Send((int)key_val, Rs | LCD_BACKLIGHT); // send digit to display.

            speed = (speed*10) + (key_val - '0');       // compute speed

            if(speed > 100){ /* Error if speed > 100% */
                LCD_SetCursor(0, 1);    // Set cursor to position (1,0)
                LCD_Write("Invalid Speed!");
                speed = 0;
            }
        }
        else if(key_val == '#'){ /* End input */
            LCD_SetCursor(0, 1);    // Set cursor to position (1,0)
            LCD_Write("DONE");

            /* set new PWM */
            set_duty_cycle(speed);

            speed = 0;
        }
        else{ /* Error if input not digit nor '#' */
            LCD_SetCursor(0, 1);    // Set cursor to position (1,0)
            LCD_Write("Invalid Input!");
            speed = 0;
        }

    }

    return 0;
}

void reset_LCD(void){
    LCD_ClearDisplay();     // Clear display
    LCD_SetCursor(0, 0);    // Set cursor to position (0,0)
    LCD_Write("Speed: 0  %");
    LCD_SetCursor(7, 0);    // Set cursor to position (7,0)
}
