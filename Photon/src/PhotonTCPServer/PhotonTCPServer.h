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
extern char TA0CCR0_REG;
// Left PWM Frequency Forward duty cycle register
extern char TA0CCR1_REG;
// Left PWM Frequency Reverse duty cycle register
extern char TA0CCR2_REG;
// Right PWM Frequency register
extern char TA2CCR0_REG;
// Right PWM Frequency Forward duty cycle register
extern char TA2CCR1_REG;
// Right PWM Frequency Reverse duty cycle register
extern char TA2CCR2_REG;
// sensor: Sensor data (-1 - +1)
extern float lastSensorPosition;

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