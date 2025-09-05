# TI_LaunchPad_Motor_LCD_Keypad_Controller
The objective of this project is to design a system that controls a DC motor using a PWM output signal, a 4x4 keypad input, and MSP430FR2355 LaunchPad. Also, it shows the motor speed from 0-100% on a 2x16 liquid crystal display (LCD). Any invalid input key or speed, the LCD displays an error message.

The DC motor requires a PWM frequency ($f_{pwm}$) between 50-100Hz (or 10-20ms period). ADC. I set the TIMERB to use a clock frequency ($f_{clk}$) 32.768kHz from the internal clock ACLK and count from 0 ($cnt_{min}$) to 600 (𝑐𝑛𝑡<sub>𝑚𝑎𝑥</sub>). Based on the equation below, reach a PWM frequency of about 54.5Hz (or 18.3ms period):

$f_{pwm} = \frac{f_{clk}}{(cnt_{max} - cnt_{min} + 1)}
= \frac{32.768 Hx}{(600-0+1)}
\approx 54.5 Hz$
&nbsp;&nbsp;&nbsp;or&nbsp;&nbsp;&nbsp;
$T_{pwm} = \frac{1}{f_{pwm}} \approx 18.3 ms$


I chose a max count (𝑐𝑛𝑡<sub>𝑚𝑎𝑥</sub>) of 600 because it makes the computation of the PWM duty period a simple, lightweight multiplication by 6 of the motor speed (or PWM duty cycle). Any other value non-divisible by 100 would lead to a large and slow multiplication or division for the LaunchPad. The LaunhPad ALU does not have a multiplication nor division module, so these operations are translated to many additions and/or shifting operation. If it takes too long, could lag the LCD display or present other timing complications. Thus, 600 PWM max count leads to the lowest multiplication latency to set the motor speed and meet its frequency requirements.

