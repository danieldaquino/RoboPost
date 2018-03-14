/*===============================

	# DiffDriver
	
	This module allows you to control the motion of a differential drive robot.
	
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
	
	1. DualMotorController module
	
===============================*/

#ifndef DIFF_DRIVER_H
#define DIFF_DRIVER_H

/*=======
Includes
========*/

/*=======
Macros
========*/
// Max speed in cm/s
#define MAX_SPEED 130.0
// Wheel base in cm
#define WHEEL_BASE 20.0
#define MAX_CURVE_RADIUS 1000
// Wheel radius in cm
#define WHEEL_RADIUS 3.5

/*=======
Globals
=======*/

/*=======
Function Prototypes
========*/

/*======
~~diffDriverInit~~

Initializes the differential driver, and necessary dependencies.

MAKE SURE SCHEDULER IS INITIALIZED BEFORE CALLING THIS FUNCTION!

inputs: none
outputs: none
Globals affected: 	Timer A0, eventually the motor pins
					Encoder pins (usually P2.0 and P2.2, unless this is a mod)
					Timer A0, P1.2, P1.3, P1.4, P1.5 pins
======*/
void diffDriverInit();

/*======
~~diffDrive~~

Changes the differential drive setpoint

inputs: 
	(float) speed: The desired speed, in cm/s
	(float) curveRadius: 	The desired curvature radius, in cm.
							Positive curvature means turning right, or going clockwise
							Negative curvature means turning left, or going counter-clockwise
outputs:
	(char) Return Status:	0 means ok
							1 means too fast
							2 means curvature too small
Globals affected: 	Timer A0, eventually the motor pins
======*/
char diffDrive(float speed, float curveRadius);

/*======
~~getSpeed~~

Gets the measured robot speed

inputs: none
outputs: 
	(float) speed: measured speed of the robot in cm/s
Globals affected: none
======*/
float getSpeed();

/*======
~~getCurveRadius~~

Gets the measured robot curvature radius

inputs: none
outputs: 
	(float) curve radius: measured curvature radius of the robot.
Globals affected: none
======*/
float getCurveRadius();

#endif