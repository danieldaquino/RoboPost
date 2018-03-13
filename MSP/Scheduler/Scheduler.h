/*===============================

	# Scheduler

	This module can schedule functions to be called at a certain frequency
	
	## Resources Used
	
	1. Timer A1
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	## Modifying
	
===============================*/
#ifndef SCHEDULER_H
#define SCHEDULER_H

/*=======
Includes
========*/
#include <msp430.h>

/*=======
Macros
========*/
//MAX FREQUENCY IS 4000
#define FREQUENCY_HZ 10
#define MAX_CALLBACKS 10

/*=======
Globals
=======*/

/*=======
Function Prototypes
========*/

/*======
~~timerISR~~

This function will call all functions within its list
inputs: none
outputs: none
Globals affected: Depends on the list set.
=======*/
void timerISR(void);

/*======
~~velocityGaugeInit~~

This function initializes all parameters necessary
inputs: none
outputs: none
Globals affected: Encoder pin (usually P1.3), Timer A1 configurations
======*/
void schedulerInit(void);

/*======
~~scheduleCallback~~

Adds a function to the schedulers list. The function input will be called
periodically.

inputs: 
	(void (*)(void)) callback: the function to be called periodically.
outputs: 
	(char) Return Status: 0 is ok
						
Globals affected: none
======*/
char scheduleCallback(void (*callback) (void));

#endif