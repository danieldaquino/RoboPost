/*===============================

	# RobotGlobals
	
	This file declares all global variables related to the robot, for access from multiple modules

	Crafted by Daniel Walnut and Tim Yue
	
================================*/
#ifndef ROBOT_GLOBALS_H
#define ROBOT_GLOBALS_H

// RPMLS: Left RPM Setpoint
int RPMLS;
// RPML: Left RPM
int RPML;
// RPMRS: Right RPM Setpoint
int RPMRS;
// RPMR: Right RPM
int RPMR;
// Left PWM Frequency register
char TA0CCR0_REG;
// Left PWM Frequency Forward duty cycle register
char TA0CCR1_REG;
// Left PWM Frequency Reverse duty cycle register
char TA0CCR2_REG;
// Right PWM Frequency register
char TA2CCR0_REG;
// Right PWM Frequency Forward duty cycle register
char TA2CCR1_REG;
// Right PWM Frequency Reverse duty cycle register
char TA2CCR2_REG;
// sensor: Sensor data (-1 - +1)
float lastSensorPosition;


#endif
