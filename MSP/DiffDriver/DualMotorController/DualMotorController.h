/*===============================

	# DualMotorController
	
	This module allows you to control two motors with a closed loop speed control
	For function descriptions and usage, please visit DualMotorController.h
	
	## Resources used (by this and its children):
	
	1. P1.2 for the Motor-1 Forward FPWM output
	2. P1.3 for the Motor-1 Reverse FPWM output
	3. P2.4 for the Motor-2 Forward FPWM output
	4. P2.5 for the Motor-2 Reverse FPWM output
	5. Timer A0 to generate PWM signals to the motor 1.
	6. Timer A2 to generate PWM signals to the motor 2.
	7. P2.0 for the Motor-1 Encoder
	8. P2.2 for the Motor-2 Encoder
	9. Timer A1 to setup the Velocity Calculations.
	
	# Requirements
	
	1. DualMotorDriver module folder, on the same folder as this file.
	2. DualVelocityGauge module folder, on the same folder as this file.
	3. Scheduler module
	4. Scheduler initialized before initializing this module
	
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
#define GEAR1_MAX_SPEED 100
#define GEAR1_FREQUENCY 3000
#define GEAR2_MAX_SPEED 200
#define GEAR2_FREQUENCY 1000
#define MAX_MOTOR_SPEED 300
#define GEAR3_FREQUENCY 100

#define KP 0.3
#define KD 0.7

/*=======
Globals
=======*/

/*=======
Function Prototypes
========*/

/*======
~~motorControllerInit~~

Initializes the motor controller, and necessary drivers.

inputs: none
outputs: none
Globals affected: 	Timer A0, A2, eventually the motor pins
					Encoder pins (usually P2.0 and P2.2, unless this is a mod)
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