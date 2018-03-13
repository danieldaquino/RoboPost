/*===============================

	# DualMotorController
	
	This module allows you to control two motors with a closed loop speed control
	For function descriptions and usage, please visit DualMotorController.h
	
===============================*/


/*=======
Includes
========*/
#include "DualMotorDriver/DualMotorDriver.h"
#include "DualMotorController.h"

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
	setDutyCycle(motor, (0.5 + ((speed - getRPM(motor))/MAX_MOTOR_SPEED)*0.5));
}

void motorControllerInit() {
	velocityGaugeInit(); //Initialize Velocity Gauge
	setupPWM(); //Setup PWM, starting with 0% duty cycle
}
