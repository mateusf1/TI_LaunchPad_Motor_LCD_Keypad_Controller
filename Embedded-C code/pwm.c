/*
 * pwm.c
 *
 * Set-up/init and generates PWM signal for DC Motor
 *
 * By: Mateus A. Fernandes A. (GitHum: mateusf1)
 */

#include <msp430.h>
#include "pwm.h"

// Using Timer3_B, CC2, and P6.1 for PWM

// Init PWM & port
void pwm_init(void){
    //-- Configure GPIO -------------------------------------------------
    P6DIR |= BIT1;                      // P6.1 output
    P6SEL0 |= BIT1;                     // P6.1  options select (TB3.2)

    //-- Disable the GPIO power-on default high-impedance mode ----------
    PM5CTL0 &= ~LOCKLPM5;

    //-- Setup Timer3_B CCR ---------------------------------------------
    TB3CCR0 = 600;                      // PWM Period ~18.3ms or Freq 54.6Hz
    TB3CCTL2 = OUTMOD_7;                // CCR2 reset/set
    TB3CCR2 = 0;                        // CCR2 PWM duty cycle

    //-- Setup Timer3_B -------------------------------------------------
    TB3CTL = TBSSEL_1 | MC_1 | TBCLR;   // ACLK, up mode, clear TBR
}

void set_duty_cycle(unsigned short duty_cycle){
    TB3CCR2 = 6*duty_cycle;
}


