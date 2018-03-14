/*===============================

	# DualMotorDriver
	## Written by Daniel Walnut
	
	This module allows you to drive two motors with FPWM signals.
	For function descriptions and usage, please visit DualMotorDriver.h
	
===============================*/

/*======
Internal Macros
=======*/

/*======
Includes
=======*/
#include <msp430.h>
#include "DualMotorDriver.h"

void setDutyCycle(char motor, float D) {
	// CHECK FOR REVERSE CONDITIONS
	char fwd = 1;
	if(D < 0) {
		// We are in reverse!
		fwd = 0;
		D = -D;
	}
	// CHECK FOR SAFETY 
	if(D > MAX_DUTY_CYCLE) {
		//TOO MUCH! Limit this
		D = MAX_DUTY_CYCLE;
	}
	//Ok, let's change the duty cycle
	if(fwd) {
		// Going forward. Which motor is this?
		if(motor == 1) {
			//Motor 1 fwd. Set Motor1FWD and put the REV to ZERO duty cycle
			MOTOR_1_FWD_TIME_REG = (int) (TA0CCR0*D);
			MOTOR_1_REV_TIME_REG = 0;
			return;
		}
		else if(motor == 2) {
			MOTOR_2_FWD_TIME_REG = (int) (TA2CCR0*D);
			MOTOR_2_REV_TIME_REG = 0;
			return;
		}
	}
	else {
		if(motor == 1) {
			MOTOR_1_FWD_TIME_REG = 0;
			MOTOR_1_REV_TIME_REG = (int) (TA0CCR0*D);
			return;
		}
		else if(motor == 2) {
			MOTOR_2_FWD_TIME_REG = 0;
			MOTOR_2_REV_TIME_REG = (int) (TA2CCR0*D);
			return;
		}
	}
}

void setupPWM() {
	// SETUP TIMER A0 for motor 1
	/* 
	TASSEL_1 : ACLK
	ID_0 : /1 divider clock; 32KHz / 1 = 32KHz
	TA_MC_1 : Up mode
	TAIE_0 : Interrupts disabled
	*/
	TA0CTL = TASSEL_1 | ID_0 | MC_1;
	// 320 counts do that f = 32KHz/320 = 100Hz.
	TA0CCR0 = 320;
	
	// SETUP TIMER A2 for motor 2
	/* 
	TASSEL_1 : ACLK
	ID_0 : /1 divider clock; 32KHz / 1 = 32KHz
	TA_MC_1 : Up mode
	TAIE_0 : Interrupts disabled
	*/
	TA2CTL = TASSEL_1 | ID_0 | MC_1;
	// 320 counts do that f = 32KHz/320 = 100Hz.
	TA2CCR0 = 320;
	
	// SETUP MOTOR Timer registers
	// Motors are stopped by default
	MOTOR_1_FWD_TIME_REG = 0;
	MOTOR_1_FWD_TIME_CTL = OUTMOD_7;
	
	MOTOR_1_REV_TIME_REG = 0;
	MOTOR_1_REV_TIME_CTL = OUTMOD_7;
	
	MOTOR_2_FWD_TIME_REG = 0;
	MOTOR_2_FWD_TIME_CTL = OUTMOD_7;
	
	MOTOR_2_REV_TIME_REG = 0;
	MOTOR_2_REV_TIME_CTL = OUTMOD_7;
	
	// SETUP MOTOR PINS
	P_MOTOR_1_DIR |= MOTOR_1;
	P_MOTOR_1_SEL |= MOTOR_1;
	P_MOTOR_2_DIR |= MOTOR_2;
	P_MOTOR_2_SEL |= MOTOR_2;
}