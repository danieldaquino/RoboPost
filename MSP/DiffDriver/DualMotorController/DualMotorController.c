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
#include "../../UARTIO.h"

/*=======
Statics
========*/
static int motorSetpoints[2] = {0, 0};
static float previousDutyCycle[2] = {0, 0};

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
			// Let's shift gears depending on setpoint.
			int newFrequency;
			if(speed > GEAR2_MAX_SPEED) {
				newFrequency = GEAR3_FREQUENCY;
			}
			else if(speed > GEAR1_MAX_SPEED) {
				newFrequency = GEAR2_FREQUENCY;
			}
			else {
				newFrequency = GEAR1_FREQUENCY;
			}
			shiftFrequency(motor, newFrequency);
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
	int i;
	for(i=0;i < 2;i++) {
		float normalError;
		normalError = (motorSetpoints[i] - getRPM(i+1))/MAX_MOTOR_SPEED; // Get error (subtract block), normalize. (1/300 block)
		float newDutyCycle;
		newDutyCycle = previousDutyCycle[i] + normalError; // Integrate. (1/s block)
		//Add a saturation factor
		if(newDutyCycle > 1) {
			newDutyCycle = 1;
		}
		else if(newDutyCycle < 0) {
			newDutyCycle = 0;
		}
		setDutyCycle(i+1, newDutyCycle);
		previousDutyCycle[i] = newDutyCycle;
	}
}

void motorControllerInit() {
	velocityGaugeInit(); //Initialize Velocity Gauge
	setupPWM(); //Setup PWM, starting with 0% duty cycle
	scheduleCallback(&controlRPM);
}
