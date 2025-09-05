/*
 * pwm.h
 *
 * Set-up/init and generates PWM signal
 *
 * By: Mateus A. Fernandes A. (GitHum: mateusf1)
 */

#ifndef PWM_H_
#define PWM_H_

// Declare #defined MACROS
#define KEYPAD_ROW P3OUT
#define KEYPAD_COL (P3IN  & 0xF0)

// Declare the functions in the header:
void pwm_init(void);
void set_duty_cycle(unsigned short duty_cycle);

#endif /* PWM_H_ */

