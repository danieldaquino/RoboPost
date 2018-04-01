/*===============================

	# PhotonTCPServer
	
	This Module acts as a TCP server for the Node.js Backend
	
	# Requirements
	
	1. RobotGlobals.h, located on one folder level above this one.

================================*/
#ifndef PHOTON_TCP_SERVER_H
#define PHOTON_TCP_SERVER_H

/*======
Externally defined variables
=======*/

// RPMLS: Left RPM Setpoint
extern float RPMLS;
// RPML: Left RPM
extern float RPML;
// RPMRS: Right RPM Setpoint
extern float RPMRS;
// RPMR: Right RPM
extern float RPMR;
// PWMLFWD: Left PWM Forward DutyCycle (0-1)
extern float PWMLFWD;
// PWMLREV: Left PWM Reverse DutyCycle (0-1)
extern float PWMLREV;
// PWMRFWD: Right PWM Forward DutyCycle (0-1)
extern float PWMRFWD;
// PWMRREV: Right PWM Reverse DutyCycle (0-1)
extern float PWMRREV;
// sensor: Sensor data (-1 - +1)
extern float sensor;

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