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

/*=======
Static variables
=======*/
static void (*callbacks[MAX_CALLBACKS])(void);
static int callbackSchedulePointer = 0;

void schedulerInit(void) {
	//Setup TimerA1 for velocity measurements
	// TASSEL_1: ACLK = 32KHz
	// ID_3: Divide by 8. We are at 4KHz
	// MC_1: Up mode. Counts to TA1CCR0
	TA1CTL = TASSEL_1 | ID_3 | MC_1 | TAIE;
	TA1CTL &= ~TAIFG; //Clear interrupts
	TA1CCR0 = (4000/FREQUENCY_HZ); // Make interrupts happen at the right frequency
	P4DIR |= GREEN_LED;
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

#pragma vector = TIMER1_A1_VECTOR
__interrupt void timerISR(void) {
	// Enable global interrupts 
	// __bis_SR_register(GIE);
	// Call all Callbacks
	int i;
	
	//Indicate computation start
	P4OUT |= GREEN_LED;
	
	for(i=0; i < callbackSchedulePointer; i++) {
		callbacks[i]();
	}	
	
	// Clear interrupt flag
	TA1CTL &= ~TAIFG; // Clear interrupt flag
	
	//Indicate computation end
	P4OUT &= ~GREEN_LED;
}

