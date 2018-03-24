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
			
===============================*/
#ifndef START_STOP_H
#define START_STOP_H

/*================
	
	~~ setupStartStop ~~
	
	This function will init the safe motor power function.
	
================*/
void setupSafeMotorPower();

#endif