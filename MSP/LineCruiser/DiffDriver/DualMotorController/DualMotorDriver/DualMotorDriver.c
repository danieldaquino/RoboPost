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
#include "../../../../Scheduler/Scheduler.h"

/*======
Statics
=======*/
static float d[2];
// Is the motor braking? 0 means no, 1 means yes
unsigned char braking[2];

static unsigned int new_MOTOR_1_FWD_TIME_REG;
static unsigned int new_MOTOR_2_FWD_TIME_REG;

static unsigned int new_MOTOR_1_REV_TIME_REG;
static unsigned int new_MOTOR_2_REV_TIME_REG;

static unsigned int new_MOTOR_1_FREQ_REG;
static unsigned int new_MOTOR_2_FREQ_REG;

/*======
Functions
=======*/


void setDutyCycle(char motor, float D) {
	// CHECK FOR REVERSE CONDITIONS
	char fwd = 1;
	if(motor == 1 || motor == 2) {
		// Save this PWM and braking if we need to change frequency
		d[motor-1] = D;
		braking[motor-1] = 0;
	}
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
			new_MOTOR_1_FWD_TIME_REG = (unsigned int) (new_MOTOR_1_FREQ_REG*D);
			new_MOTOR_1_REV_TIME_REG = 0;
			return;
		}
		else if(motor == 2) {
			new_MOTOR_2_FWD_TIME_REG = (unsigned int) (new_MOTOR_2_FREQ_REG*D);
			new_MOTOR_2_REV_TIME_REG = 0;
			return;
		}
	}
	else {
		if(motor == 1) {
			new_MOTOR_1_FWD_TIME_REG = 0;
			new_MOTOR_1_REV_TIME_REG = (unsigned int) (new_MOTOR_1_FREQ_REG*D);
			return;
		}
		else if(motor == 2) {
			new_MOTOR_2_FWD_TIME_REG = 0;
			new_MOTOR_2_REV_TIME_REG = (unsigned int) (new_MOTOR_2_FREQ_REG*D);
			return;
		}
	}
}

void brake(char motor, float D) {
	if(motor == 1 || motor == 2) {
		// Save this PWM and braking if we need to change frequency
		d[motor-1] = D;
		braking[motor-1] = 1;
	}
	if(D < 0) {
		// Not allowed
		D = 0;
	}
	
	// CHECK FOR SAFETY 
	if(D > MAX_DUTY_CYCLE) {
		// TOO MUCH! Limit this
		D = MAX_DUTY_CYCLE;
	}
	
	if(motor == 1) {
		//Motor 1 fwd. Set Motor1FWD and put the REV to ZERO duty cycle
		new_MOTOR_1_FWD_TIME_REG = (unsigned int) (new_MOTOR_1_FREQ_REG*D);
		new_MOTOR_1_REV_TIME_REG = (unsigned int) (new_MOTOR_1_FREQ_REG*D);
		return;
	}
	else if(motor == 2) {
		new_MOTOR_2_FWD_TIME_REG = (unsigned int) (new_MOTOR_2_FREQ_REG*D);
		new_MOTOR_2_REV_TIME_REG = (unsigned int) (new_MOTOR_2_FREQ_REG*D);
		return;
	}
}

char shiftFrequency(char motor, unsigned int frequency) {
	if(frequency > MAX_FREQUENCY || frequency < MIN_FREQUENCY) {
		// Bad input
		return 1;
	}
	if(motor == 1) {
		new_MOTOR_1_FREQ_REG = (SMCLK_FREQUENCY/4)/frequency;
		// This prevents big big spikes on shifting.
		if(braking) {
			brake(1, d[0]);
		}
		else {
			setDutyCycle(1, d[0]);
		}
	}
	else if(motor == 2) {
		new_MOTOR_2_FREQ_REG = (SMCLK_FREQUENCY/4)/frequency;		
		// This prevents big big spikes on shifting.
		if(braking) {
			brake(2, d[1]);
		}
		else {
			setDutyCycle(2, d[1]);
		}
	}
	else {
		// Bad input.
		return 1;
	}
	return 0;
}

void updateMotors() {
	// Update forward pwms
	MOTOR_1_FWD_TIME_REG = new_MOTOR_1_FWD_TIME_REG;
	MOTOR_2_FWD_TIME_REG = new_MOTOR_2_FWD_TIME_REG;

	// Update reverse pwms
	MOTOR_1_REV_TIME_REG = new_MOTOR_1_REV_TIME_REG;
	MOTOR_2_REV_TIME_REG = new_MOTOR_2_REV_TIME_REG;

	// Update frequency on pwms
	MOTOR_1_FREQ_REG = new_MOTOR_1_FREQ_REG;
	MOTOR_2_FREQ_REG = new_MOTOR_2_FREQ_REG;
}

void setupPWM() {
	// SETUP TIMER A0 for motor 1
	/* 
	TASSEL_2 : SMCLK
	ID_2 : /4 divider clock; 16MHz / 4 = 4MHz
	MC_1 : Up mode
	*/
	TA0CTL = TASSEL_2 | ID_2 | MC_1;
	// 40000 counts do that f = 4MHz/40000 = 100Hz.
	new_MOTOR_1_FREQ_REG = 40000;
	MOTOR_1_FREQ_REG = 40000;
	
	// SETUP TIMER A2 for motor 2
	/* 
	TASSEL_1 : SMCLK
	ID_2 : /1 divider clock; 16MHz / 4 = 4MHz
	MC_1 : Up mode
	*/
	TA2CTL = TASSEL_2 | ID_2 | MC_1;
	// 40000 counts do that f = 4MHz/40000 = 100Hz.
	new_MOTOR_2_FREQ_REG = 40000;
	MOTOR_2_FREQ_REG = 40000;
	
	// SETUP MOTOR Timer registers
	// Motors are stopped by default
	new_MOTOR_1_FWD_TIME_REG = 0;
	MOTOR_1_FWD_TIME_REG = 0;
	MOTOR_1_FWD_TIME_CTL = OUTMOD_7;
	
	new_MOTOR_1_REV_TIME_REG = 0;
	MOTOR_1_REV_TIME_REG = 0;
	MOTOR_1_REV_TIME_CTL = OUTMOD_7;
	
	new_MOTOR_2_FWD_TIME_REG = 0;
	MOTOR_2_FWD_TIME_REG = 0;
	MOTOR_2_FWD_TIME_CTL = OUTMOD_7;
	
	new_MOTOR_2_REV_TIME_REG = 0;
	MOTOR_2_REV_TIME_REG = 0;
	MOTOR_2_REV_TIME_CTL = OUTMOD_7;
	
	// SETUP MOTOR PINS
	P_MOTOR_1_DIR |= MOTOR_1;
	P_MOTOR_1_SEL |= MOTOR_1;
	P_MOTOR_2_DIR |= MOTOR_2;
	P_MOTOR_2_SEL |= MOTOR_2;
	
	// Initialize Duty cycle buffers to zero
	d[0] = 0;
	d[1] = 0;
	braking[0] = 0;
	braking[1] = 0;
	
	// Schedule the motor outputs
	scheduleOutputCallback(&updateMotors);
}