/*===============================

	# PhotonTCPServer
	
	This Module acts as a TCP server for the Node.js Backend
	
	# Requirements
	
	1. RobotGlobals.h, located on one folder level above this one.

================================*/
#ifndef PHOTON_TCP_SERVER_H
#define PHOTON_TCP_SERVER_H

/*======
Macros
=======*/
// Maximum size for JSON buffers. Depends on how big is the data you're sending.
#define JSON_MAX_SIZE 500
// How often the measurements will be sent, in milliseconds
#define MSTREAM_REFRESH_PERIOD 100

/*======
Externally defined variables
=======*/

// RPMLS: Left RPM Setpoint
extern int RPMLS;
// RPML: Left RPM
extern int RPML;
// RPMRS: Right RPM Setpoint
extern int RPMRS;
// RPMR: Right RPM
extern int RPMR;
// Left PWM Frequency register
extern int TA0CCR0_REG;
// Left PWM Frequency Forward duty cycle register
extern int TA0CCR1_REG;
// Left PWM Frequency Reverse duty cycle register
extern int TA0CCR2_REG;
// Right PWM Frequency register
extern int TA2CCR0_REG;
// Right PWM Frequency Forward duty cycle register
extern int TA2CCR1_REG;
// Right PWM Frequency Reverse duty cycle register
extern int TA2CCR2_REG;
// sensor: Sensor data (-1 - +1)
extern float lastSensorPosition;
//color sensor
extern float Color;
//desired speed
extern float Desired_Speed;

extern char robotPlay; //  A “1” indicates the robot has to start running. A “0” indicates a stop signal.
extern unsigned long int timeStamp; //  TimeStamp of SPI receival

extern char sharpestCurve; // Tightest curve radius in cm
extern float cruiseKp; // Proportional gain of the lineCruiser
extern float cruiseKd; // Differential gain of the lineCruiser
extern float corneringDBrakeFactor; // Number between 0 and 1 to tell how much to slow down in tightening curves. 0 means never slows down. 1 means full stop on tightest curve.
extern float corneringPBrakeFactor; // Number between 0 and 1 to tell how much to slow down in a given curve. 0 means never slows down. 1 means full stop on tightest curve.
extern float motorKp; // Proportional gain of the motors.
extern float motorKd; // Differential gain of the motors.


/*======
	~~PhotonTCPServerInit~~

	Loops the TCP Server

	inputs: none
	outputs: none

======*/
void PhotonTCPServerLoop();

/*======
	~~PhotonTCPServerInit~~

	Starts the TCP server

	inputs: none
	outputs: none

======*/
void PhotonTCPServerInit();

#endif