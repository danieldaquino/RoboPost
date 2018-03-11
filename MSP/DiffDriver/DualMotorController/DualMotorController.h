/*===============================

	# DualMotorController
	## Written by Daniel Walnut
	
	This module allows you to control two motors with a closed loop speed control
	For function descriptions and usage, please visit DualMotorController.h
	
	## Resources used (by this and its children):
	
	1. P1.2 for the Motor-1 Forward PWM output
	2. P1.3 for the Motor-1 Reverse PWM output
	3. P1.4 for the Motor-2 Forward PWM output
	4. P1.5 for the Motor-2 Reverse PWM output
	5. Timer A0 to generate PWM signals to the motors.
	6. P2.0 for the Motor-1 Encoder
	7. P2.2 for the Motor-2 Encoder
	8. Timer A1 to setup the Velocity Calculations.
	
	# Requirements
	
	1. DualMotorDriver module folder, on the same folder as this file.
	2. DualVelocityGauge module folder, on the same folder as this file.
	
===============================*/

#ifndef DUAL_MOTOR_CONTROLLER_H
#define DUAL_MOTOR_CONTROLLER_H

/*=======
Includes
========*/
#include <msp430.h>
#include "DualVelocityGauge/DualVelocityGauge.h"

/*=======
Macros
========*/
#define MAX_MOTOR_SPEED 300

/*=======
Globals
=======*/

/*=======
Function Prototypes
========*/

/*======
~~motorControllerInit~~

Initializes the motor controller, and necessary drivers.

inputs: 
	(char) motor to be selected. either 1 or 2 please.
	(int) Desired speed, from -MAX_MOTOR_SPEED to MAX_MOTOR_SPEED
outputs: 
	(char) Return status:	0 means "ok"
							1 means "out of bounds, went to max"
							2 means "No motor found"
Globals affected: Timer A0, eventually the motor pins
======*/
void motorControllerInit();

/*======
~~setRPM~~

Sets the desired speed of the Motor

inputs: 
	(char) motor to be selected. either 1 or 2 please.
	(int) Desired speed, from -MAX_MOTOR_SPEED to MAX_MOTOR_SPEED
outputs: 
	(char) Return status:	0 means "ok"
							1 means "out of bounds, went to max"
							2 means "No motor found"
Globals affected: Timer A0, eventually the motor pins
======*/
char setRPM(char motor, int speed);


#endif