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
			
===============================*/
#ifndef START_STOP_H
#define START_STOP_H

/*================
	
	~~ setupStartStop ~~
	
	This function will init the safe motor power function.
	
	Globals affected: Port 1, P1.0, P1.1
	
================*/
void setupSafeMotorPower();

/*================
	
	~~ stopRobot ~~
	
	This function will stop the robot. Press S2 to start.
	
	Globals affected:	Port 1, P1.0, P1.1, Interrupts get disabled then enabled.
						TA[0,2]CCR[1,2] also get reset.
	
================*/
void stopRobot();


#endif