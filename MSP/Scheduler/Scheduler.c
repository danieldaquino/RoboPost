/*===============================

	# Scheduler

	This module can schedule functions to be called at a certain frequency
	
	## Resources Used
	
	1. Timer A1
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	## Modifying
	
===============================*/

/*=======
Includes
========*/
#include <msp430.h>
#include "Scheduler.h"
#include "../StartStop/StartStop.h"

/*=======
Static variables
=======*/
static int callbackScheduleInputPointer = 0;
static void (*inputCallbacks[MAX_CALLBACKS])(void);

static int callbackSchedulePointer = 0;
static void (*callbacks[MAX_CALLBACKS])(void);

static int callbackScheduleOutputPointer = 0;
static void (*outputCallbacks[MAX_CALLBACKS])(void);

// compute Flag indicates if computation has to be done or not.
static char computeFlag;

void schedulerInit(void) {
	//Setup TimerA1 for velocity measurements
	// TASSEL_1: ACLK = 32KHz
	// ID_3: Divide by 8. We are at 4KHz
	// MC_1: Up mode. Counts to TA1CCR0
	TA1CTL = TASSEL_1 | ID_3;
	TA1CTL &= ~TAIFG; //Clear interrupts
	TA1CCR0 = (4000/FREQUENCY_HZ); // Make interrupts happen at the right frequency
	
	P4DIR |= GREEN_LED;
	P_CMPT_DIR |= CMPT;
	P_CMPT_OUT &= ~CMPT;
	
	schedulerCanRun = 1;
	computeFlag = 0;
}

void schedulerRun(void) {
	
	// ****** Prepare Scheduler for initial run!! ***********
	TA1CTL &= ~TAIFG; // Clear interrupts first
	// MC_1: Up mode. Counts to TA1CCR0
	TA1CTL |= TAIE | MC_1; // Start timer and enable interrupts
	computeFlag = 1; // Tell it to compute.
	// ******************************************************
	
	while(schedulerCanRun) {
		//*****************************
		if(!computeFlag) {
			// False trigger. Go back.
			continue;
		}
		//Indicate computation start
		P4OUT |= GREEN_LED;
		//*****************************
		
		// Call all input callbacks
		int i;
		for(i=0; i < callbackScheduleInputPointer; i++) {
			P_CMPT_OUT |= CMPT;
			inputCallbacks[i]();
			P_CMPT_OUT &= ~CMPT;
		}
		
		// Call all Callbacks
		for(i=0; i < callbackSchedulePointer; i++) {
			P_CMPT_OUT |= CMPT;
			callbacks[i]();
			P_CMPT_OUT &= ~CMPT;
		}
		
		//*****************************
		//Indicate computation end
		P4OUT &= ~GREEN_LED;
		computeFlag = 0;	// Computing finished.
		//********************************************************
		_bis_SR_register(CPUOFF + GIE);
		//************** Nothing below this **********************
	}
}

char scheduleInputCallback(void (*callback) (void)) {
	if(callbackScheduleInputPointer < MAX_CALLBACKS) {
		inputCallbacks[callbackScheduleInputPointer] = callback;
		callbackScheduleInputPointer++;
		return 0;
	}
	else {
		return -1;
	}
}

char scheduleCallback(void (*callback) (void)) {
	if(callbackSchedulePointer < MAX_CALLBACKS) {
		callbacks[callbackSchedulePointer] = callback;
		callbackSchedulePointer++;
		return 0;
	}
	else {
		return -1;
	}
}

char scheduleOutputCallback(void (*callback) (void)) {
	if(callbackScheduleOutputPointer < MAX_CALLBACKS) {
		outputCallbacks[callbackScheduleOutputPointer] = callback;
		callbackScheduleOutputPointer++;
		return 0;
	}
	else {
		return -1;
	}
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void timerISR(void) {
	if(computeFlag == 0) {
		// Computing was done! Call all output Callbacks
		int i;
		for(i=0; i < callbackScheduleOutputPointer; i++) {
			outputCallbacks[i]();
		}
	}
	else {
		// error! handle it
		offlineStopRobotOperations();
	}
	TA1CTL &= ~TAIFG; // Clear interrupt flag
	__bic_SR_register_on_exit(CPUOFF); // Turn on the CPU!!
	computeFlag = 1; // Start computations again!
}
