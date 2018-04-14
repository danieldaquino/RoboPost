/*===============================

	# Scheduler

	This module can schedule functions to be called at a certain frequency
	
	## Resources Used
	
	1. Timer A1
	2. P4.7 LED
	3. StartStop module
	4. P6.2 Computing Indicator
		
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
#define GREEN_LED BIT7
#define RED_LED BIT0

// Computing signal pin mask. Will be high when processing input or compute callback. will provide edges to separate each callback.
#define CMPT BIT2
#define P_CMPT_DIR P6DIR
#define P_CMPT_OUT P6OUT

/*=======
Globals
=======*/
// Normally 1 after Initialization. 1 will make it continue running. 0 breaks the scheduler loop.
char schedulerCanRun;

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
~~schedulerRun~~

This function begins scheduler routines.
This takes over the CPU and should never return under normal circumstances

inputs: none
outputs: no
Globals affected:	Depends on the Scheduled functions. Look for "scheduleCallback" calls for more.
					Takes over control of main routine of the CPU
======*/
void schedulerRun(void);

/*======
~~scheduleInputCallback~~

Adds a function to the input schedulers list. The function input will be called
periodically.

inputs: 
	(void (*)(void)) callback: the function to be called to input.
outputs: 
	(char) Return Status: 0 is ok
						
Globals affected: none
======*/
char scheduleInputCallback(void (*callback) (void));

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

/*======
~~scheduleOutputCallback~~

Adds a function to the output schedulers list. The function input will be called
periodically.

inputs: 
	(void (*)(void)) callback: the function to be called to output. Should be short.
outputs: 
	(char) Return Status: 0 is ok
						
Globals affected: none
======*/
char scheduleOutputCallback(void (*callback) (void));

#endif