/*===============================

	# DualMotorDriver
	## by Daniel Walnut and Tim Yue
	
	This module allows you to control two motors with a closed loop speed control
	
	## Resources used:
	
	1. P1.2 for the Motor-1 Forward PWM output
	2. P1.3 for the Motor-1 Reverse PWM output
	3. P1.4 for the Motor-2 Forward PWM output
	4. P1.5 for the Motor-2 Reverse PWM output
	5. Timer A0 to generate PWM signals to the motors.
	
	## Customizing
	
	1. Use the same Port for both Motors. Otherwise significant changes to code will have to be made
	
===============================*/

#ifndef DUAL_MOTOR_DRIVER_H
#define DUAL_MOTOR_DRIVER_H

/*=======
Macros
========*/
#define P_MOTORS_OUT P1OUT
#define P_MOTORS_DIR P1DIR
#define P_MOTORS_IN P1IN
#define P_MOTORS_SEL P1SEL
#define P_MOTORS_IE P1IE
#define P_MOTORS_IFG P1IFG
#define P_MOTORS_IV P1IV
#define P_MOTORS_REN P1REN

#define MOTOR_1_FWD BIT2
#define MOTOR_1_REV BIT3
#define MOTOR_2_FWD BIT4
#define MOTOR_2_REV BIT5
// MOTORS mask for added safety
#define MOTORS (MOTOR_1_FWD | MOTOR_1_REV | MOTOR_2_FWD | MOTOR_2_REV)
// If you change the pins, make sure to change the corresponding two on the bottom.
// Make sure to check the MSP430 pinout
#define MOTOR_1_FWD_TIME_REG TA0CCR1
#define MOTOR_1_FWD_TIME_CTL TA0CCTL1
#define MOTOR_1_REV_TIME_REG TA0CCR2
#define MOTOR_1_REV_TIME_CTL TA0CCTL2
#define MOTOR_2_FWD_TIME_REG TA0CCR3
#define MOTOR_2_FWD_TIME_CTL TA0CCTL3
#define MOTOR_2_REV_TIME_REG TA0CCR4
#define MOTOR_2_REV_TIME_CTL TA0CCTL4

#define MAX_DUTY_CYCLE 0.8

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
Globals affected: Timer A0, P1.2 pin
=======*/
void setupPWM();

/*======
~~setDutyCycle~~

function to change the duty cycle to a specified value in either motor 1 or 2.
Since both motors have two directions, if a negative duty cycle is input,
the reverse signal will be PWM'ed, and motor will spin to the other direction.
DO NOT REVERSE THE MOTOR DUTY CYCLE WITHOUT BRAKING FIRST!!!

inputs:
	(char) Motor Mask to be selected. please use 1 or 2
	(double) Duty cycle, from 0 to 1
	
outputs: none
Globals affected: Timer A0
=======*/
void setDutyCycle(char motor, double D);

#endif