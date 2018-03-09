/*===============================

	PWMMotor
	
	this C module is part of the MSP Motor Control.
	It provides functions that allow you to Control a Motor a PWM signal.
	
	Written by Daniel Walnut
	
	Requirements for use:
		
	P1.2 must be free for the motor PWM output
	
	Timer A0 must be free too.
	
	Refer to PWMMotor.h to see the description of functions.
	
===============================*/

#include <msp430.h>
#include "PWMMotor.h"

void setDutyCycle(double D) {
	if(D > MAX_DUTY_CYCLE) {
		//TOO MUCH! Limit this
		D = MAX_DUTY_CYCLE;
	}
	if(D < 0) {
		D = 0;
	}
	//Ok, let's change the duty cycle
	TA0CCR1 = (int) (160*D);
}

void setupPWM() {
	//PWM will be generated from Timer A0
	// TASSEL_1 : ACLK
	// TA_ID_1 : /2 divider clock
	// TA_MC_1 : Up mode
	// TAIE_0 : Interrupts disabled
	P_MOTOR_DIR |= MOTOR_BIT;
	P_MOTOR_SEL |= MOTOR_BIT;
	// 160 counts do that f = 16KHz/160 = 100Hz.
	// 160 - 1 because CCR0 is included in count
	TA0CCR0 = 159;
	// 50% duty cycle default
	TA0CCR1 = 80;
	TA0CCTL1 = OUTMOD_7;
	// 32KHz / 2 = 16KHz
	TA0CTL = TASSEL_1 | ID_1 | MC_1;
}
