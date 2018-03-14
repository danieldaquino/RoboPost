/*===============================

	# DualMotorDriver
	
	This module allows you to drive two motors with PWM signals
	
	## Requirements
	1. Two DC motors
	2. Two TI DRV8871 Motor drivers
	
	## Resources used:
	
	1. P1.2 for the Motor-1 Forward PWM output
	2. P1.3 for the Motor-1 Reverse PWM output
	3. P2.4 for the Motor-2 Forward PWM output
	4. P2.5 for the Motor-2 Reverse PWM output
	5. Timer A0 to generate PWM signals to the motor 1.
	6. Timer A2 to generate PWM signals to the motor 2.
	
	## Customizing
	
===============================*/

#ifndef DUAL_MOTOR_DRIVER_H
#define DUAL_MOTOR_DRIVER_H

/*=======
Macros
========*/
#define P_MOTOR_1_OUT P1OUT
#define P_MOTOR_1_DIR P1DIR
#define P_MOTOR_1_IN P1IN
#define P_MOTOR_1_SEL P1SEL
#define P_MOTOR_1_IE P1IE
#define P_MOTOR_1_IFG P1IFG
#define P_MOTOR_1_IV P1IV
#define P_MOTOR_1_REN P1REN

#define P_MOTOR_2_OUT P2OUT
#define P_MOTOR_2_DIR P2DIR
#define P_MOTOR_2_IN P2IN
#define P_MOTOR_2_SEL P2SEL
#define P_MOTOR_2_IE P2IE
#define P_MOTOR_2_IFG P2IFG
#define P_MOTOR_2_IV P2IV
#define P_MOTOR_2_REN P2REN

#define MOTOR_1_FWD BIT2
#define MOTOR_1_REV BIT3
#define MOTOR_2_FWD BIT4
#define MOTOR_2_REV BIT5

// MOTORS mask for added safety
#define MOTOR_1 (MOTOR_1_FWD | MOTOR_1_REV)
#define MOTOR_2 (MOTOR_2_FWD | MOTOR_2_REV)
// If you change the pins, make sure to change the corresponding two on the bottom.
// Make sure to check the MSP430 pinout
#define MOTOR_1_FWD_TIME_REG TA0CCR1
#define MOTOR_1_FWD_TIME_CTL TA0CCTL1
#define MOTOR_1_REV_TIME_REG TA0CCR2
#define MOTOR_1_REV_TIME_CTL TA0CCTL2
#define MOTOR_2_FWD_TIME_REG TA2CCR1
#define MOTOR_2_FWD_TIME_CTL TA2CCTL1
#define MOTOR_2_REV_TIME_REG TA2CCR2
#define MOTOR_2_REV_TIME_CTL TA2CCTL2

#define MAX_DUTY_CYCLE 0.8
#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 3000

/*=======
Globals
=======*/


/*=======
Function Prototypes
=======*/

/*======
~~setupPWM~~

Sets up timer A for PWM

inputs: none
outputs: none
Globals affected: Timer A0, A2, and motor pins
=======*/
void setupPWM();

/*======
~~shiftFrequency~~

function to change the frequency. Use higher frequencies if you want to achieve lower stable speeds
Use 100Hz for high stable speeds.

inputs:
	(char) Motor to be selected. please use 1 or 2
	(int) frequency: frequency within the established range in MACROS
outputs: return status... 0 is ok. 1 means failed.
Globals affected: Timer A0 or Timer A2
=======*/
char shiftFrequency(char motor, int frequency);

/*======
~~setDutyCycle~~

function to change the duty cycle to a specified value in either motor 1 or 2.
Since both motors have two directions, if a negative duty cycle is input,
the reverse signal will be PWM'ed, and motor will spin to the other direction.
DO NOT REVERSE THE MOTOR DUTY CYCLE WITHOUT BRAKING FIRST!!!

inputs:
	(char) Motor to be selected. please use 1 or 2
	(float) Duty cycle, from 0 to 1
	
outputs: none
Globals affected: Timer A0, eventually Motor pins
=======*/
void setDutyCycle(char motor, float D);

#endif