/*===============================

	# DualMotorController
	
	This module allows you to control two motors with a closed loop speed control
	For function descriptions and usage, please visit DualMotorController.h
	
===============================*/


/*=======
Includes
========*/
#include <msp430.h>
#include "DualMotorDriver/DualMotorDriver.h"
#include "DualMotorController.h"
#include "../../Scheduler/Scheduler.h"

/*=======
Statics
========*/
static int motorSetpoints[2] = {0, 0};

/*=======
Function Definitions
========*/
char setRPM(char motor, int speed) {
	/*
	Here is how it works
	1. it measures the error.
	2. it normalizes the error with MAX_MOTOR_SPEED
	3. It calculates the duty cycle assuming that zero error means 50% duty cycle,
	   that maximum positive error means 100% duty cycle,
	   and that maximum negative error means 0% duty cycle.
	*/
	if(motor == 1 || motor == 2) {
		if(speed < MAX_MOTOR_SPEED && speed > -MAX_MOTOR_SPEED) {
			motorSetpoints[motor-1] = speed;
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 2;
	}
}

static void controlRPM() {
	setDutyCycle(1, (0.5 + ((motorSetpoints[0] - getRPM(1))/MAX_MOTOR_SPEED)*0.5));	
	setDutyCycle(2, (0.5 + ((motorSetpoints[1] - getRPM(2))/MAX_MOTOR_SPEED)*0.5));	
}

void motorControllerInit() {
	velocityGaugeInit(); //Initialize Velocity Gauge
	setupPWM(); //Setup PWM, starting with 0% duty cycle
	scheduleCallback(&controlRPM);
}
