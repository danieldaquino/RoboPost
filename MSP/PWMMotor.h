/*===============================

	PWMMotor
	
	this C module is part of the MSP Motor Control.
	It provides functions that allow you to Control a Motor a PWM signal.
	
	Written by Daniel Walnut
	
	Requirements for use:
		
	P1.2 must be free for the motor PWM output
	
	Timer A0 must be free too.
	
===============================*/

#ifndef PWMMOTOR_H
#define PWMMOTOR_H

/*=======
Macros
========*/
#define P_MOTOR_OUT P1OUT
#define P_MOTOR_DIR P1DIR
#define P_MOTOR_IN P1IN
#define P_MOTOR_SEL P1SEL
#define P_MOTOR_IE P1IE
#define P_MOTOR_IFG P1IFG
#define P_MOTOR_IV P1IV
#define P_MOTOR_REN P1REN

#define MOTOR_BIT BIT2

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

function to change the duty cycle to a specified value

inputs: Duty cycle, from 0 to 1
outputs: none
Globals affected: Timer A0
=======*/
void setDutyCycle(double D);

#endif