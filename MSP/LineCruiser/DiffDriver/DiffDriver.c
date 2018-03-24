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

/*=======
Includes
========*/
#include "DualMotorController/DualMotorController.h"
#include "DiffDriver.h"

/*=======
Statics
========*/

/*=======
Static Function Prototypes
========*/
/*======
~~getWheelLinearSpeed~~

Gets the measured linear speed of one wheel

inputs: 
	(char) wheel: 1 or 2, L/R
outputs: 
	(float) speed: measured speed of the wheel in cm/s
Globals affected: none
======*/
inline static float getWheelLinearSpeed(char wheel);


/*=======
Functions
========*/

void diffDriverInit() {
	motorControllerInit();
	// Make sure robot is stopped in the beginning.
	setRPM(1, 0);
	setRPM(2, 0);	
}

char diffDrive(float speed, float curveRadius) {
	// Check for bad inputs
	if(speed > MAX_SPEED) {
		speed = MAX_SPEED;
	}
	if(curveRadius < WHEEL_BASE/2 && curveRadius >= 0) {
		curveRadius = WHEEL_BASE/2;
	}
	else if(curveRadius > -WHEEL_BASE/2 && curveRadius < 0) {
		curveRadius = -WHEEL_BASE/2;
	}
	// Approximate huge curvature radius to a straight line
	if(curveRadius > MAX_CURVE_RADIUS) {
		// Just go straight...
		float RPM1;
		RPM1 = (speed/WHEEL_RADIUS)/(0.105);
		float RPM2;
		RPM2 = (speed/WHEEL_RADIUS)/(0.105);
		// Apply setpoint
		setRPM(1, (int) RPM1);
		setRPM(2, (int) RPM2);
		return 0;
	}
	else {
		// Calculate the radii
		float radius1;
		radius1 = curveRadius + WHEEL_BASE/2;
		float radius2;
		radius2 = curveRadius - WHEEL_BASE/2;
		// Calc angular speed around the curvature radius
		float angularSpeed;
		angularSpeed = speed/curveRadius;
		// Calc linear speed of each wheel
		float linearSpeed1;
		linearSpeed1 = angularSpeed*radius1;
		float linearSpeed2;
		linearSpeed2 = angularSpeed*radius2;
		// Calc RPM for each wheel
		float RPM1;
		RPM1 = (linearSpeed1/WHEEL_RADIUS)/(0.105);
		float RPM2;
		RPM2 = (linearSpeed2/WHEEL_RADIUS)/(0.105);
		// Apply setpoint
		setRPM(1, (int) RPM1);
		setRPM(2, (int) RPM2);
		return 0;
	}
}

float getSpeed() {
	float speed1;
	speed1 = getWheelLinearSpeed(1);
	float speed2;
	speed2 = getWheelLinearSpeed(2);
	// The actual speed is the arithmetic mean of the linear speed of both wheels
	return (speed1 + speed2)/2;
}

inline static float getWheelLinearSpeed(char wheel) {
	// 2*pi/60 ==> 0.105. This is conversion factor from RPM to rad/s
	return getRPM(wheel)*(0.105)*WHEEL_RADIUS;
}

float getCurveRadius() {
	float speed1;
	speed1 = getWheelLinearSpeed(1);
	float speed2;
	speed2 = getWheelLinearSpeed(2);
	return (WHEEL_BASE*(speed1+speed2))/(2*(speed1-speed2));
}
