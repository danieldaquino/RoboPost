/*===============================

	# DualMotorDriver
	## Written by Daniel Walnut
	
	This module allows you to control two motors with a closed loop speed control
	For function descriptions and usage, please visit VelocityGauge.h
	
===============================*/

/*======
Internal Macros
=======*/
// Register value for 100% duty cycle
#define DUTY_100_REG 160.0 

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
			MOTOR_1_FWD_TIME_REG = (int) (DUTY_100_REG*D);
			MOTOR_1_REV_TIME_REG = 0;
			return;
		}
		else if(motor == 2) {
			MOTOR_2_FWD_TIME_REG = (int) (DUTY_100_REG*D);
			MOTOR_2_REV_TIME_REG = 0;
			return;
		}
	}
	else {
		if(motor == 1) {
			MOTOR_1_FWD_TIME_REG = 0;
			MOTOR_1_REV_TIME_REG = (int) (DUTY_100_REG*D);
			return;
		}
		else if(motor == 2) {
			MOTOR_2_FWD_TIME_REG = 0;
			MOTOR_2_REV_TIME_REG = (int) (DUTY_100_REG*D);
			return;
		}
	}
}

void setupPWM() {
	// SETUP TIMER A0
	// PWM will be generated from Timer A0
	/* 
	TASSEL_1 : ACLK
	TA_ID_1 : /2 divider clock; 32KHz / 2 = 16KHz
	TA_MC_1 : Up mode
	TAIE_0 : Interrupts disabled
	*/
	TA0CTL = TASSEL_1 | ID_1 | MC_1;
	// 160 counts do that f = 16KHz/160 = 100Hz.
	// 160 - 1 because CCR0 is included in count
	TA0CCR0 = 159;
	
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
	P_MOTORS_DIR |= MOTORS;
	P_MOTORS_SEL |= MOTORS;
}