/*===============================

	# StartStop
	
	This module allows you to stop or start operation of the robot,
	with a pushbutton 
	
	## Resources used:
	
	1. P1.1
	2. PORT1 ISR
	3. TA0CCR1
	4. TA0CCR2
	5. TA2CCR1
	6. TA2CCR2
	7. GIE
	
	## Requirements
	
	1. Color Module
	2. SPI module
			
===============================*/
#ifndef START_STOP_H
#define START_STOP_H

/*=======
Globals
========*/
char robotPlay;

/*================
	
	~~ setupStartStop ~~
	
	This function will init the safe motor power function.
	
	Globals affected: Port 1, P1.0, P1.1
	
================*/
void setupSafeMotorPower();

/*================
	
	~~ stopRobot ~~
	
	This function will stop the robot. Press S2 to start or press play on the web
	
	Globals affected:	Port 1, P1.0, P1.1, Interrupts get disabled then enabled.
						TA[0,2]CCR[1,2] also get reset.
	
================*/
void stopRobot();
/*================

    ~~ stopRobotAtStation ~~

    This function will stop the robot for as long as the color is seen.

    Globals affected:
                        TA[0,2]CCR[1,2] dynamic braking will be applied

================*/
void stopRobotAtStation();
/*================
	
	~~ offlineStopRobotOperations ~~
	
	This function will stop the robot in offline mode. Press S2 to start.
	Make sure interrupts are disabled.
	
	Globals affected:	Port 1, P1.0, P1.1.
						TA[0,2]CCR[1,2] also get reset.
	
================*/
void offlineStopRobotOperations();

/*================
	
	~~ Docking ~~
	
	This function will stop the robot if it is on a station
	
	inputs: none
	outputs: none
	
	Globals affected: Can stop schedueler, cancel scheduler, Eventually Motor pins will be affected.
	
================*/
void Docking();

/*================
	
	~~ robotPlayUpdate ~~
	
	This function will check robotPlay status from the internet. robot will stop if robotPlay is false.
	
	Globals affected:	Port 1, P1.0, P1.1, Interrupts get disabled then enabled.
						TA[0,2]CCR[1,2] also get reset.
	
================*/
void robotPlayUpdate();


#endif
