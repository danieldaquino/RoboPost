/*===============================

	# RobotGlobals
	
	This file declares all global variables related to the robot, for access from multiple modules

	Crafted by Daniel Walnut and Tim Yue
	
================================*/
#ifndef ROBOT_GLOBALS_H
#define ROBOT_GLOBALS_H

/*========
Measurements
==========*/

// RPMLS: Left RPM Setpoint
int RPMLS;
// RPML: Left RPM
int RPML;
// RPMRS: Right RPM Setpoint
int RPMRS;
// RPMR: Right RPM
int RPMR;
// Left PWM Frequency register
int TA0CCR0_REG;
// Left PWM Frequency Forward duty cycle register
int TA0CCR1_REG;
// Left PWM Frequency Reverse duty cycle register
int TA0CCR2_REG;
// Right PWM Frequency register
int TA2CCR0_REG;
// Right PWM Frequency Forward duty cycle register
int TA2CCR1_REG;
// Right PWM Frequency Reverse duty cycle register
int TA2CCR2_REG;
// sensor: Sensor data (-1 - +1)
float lastSensorPosition;

// color sensor reading
float Color;
// Desired speed
float Desired_Speed;

/*========
Controls
==========*/
char robotPlay; //  A “1” indicates the robot has to start running. A “0” indicates a stop signal.
int timeStamp;	// The time Photon received the data from SPI.

/*========
Settings
==========*/
char sharpestCurve; // Tightest curve radius in cm
float cruiseKp; // Proportional gain of the lineCruiser
float cruiseKd; // Differential gain of the lineCruiser
float corneringDBrakeFactor; // Number between 0 and 1 to tell how much to slow down in tightening curves. 0 means never slows down. 1 means full stop on tightest curve.
float corneringPBrakeFactor; // Number between 0 and 1 to tell how much to slow down in a given curve. 0 means never slows down. 1 means full stop on tightest curve.
float motorKp; // Proportional gain of the motors.
float motorKd; // Differential gain of the motors.

#endif
