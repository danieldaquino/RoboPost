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

/*======
Includes
=======*/
#include "StartStop.h"
#include <msp430.h>

/*======
Macros
=======*/
#define BUTTON_1 BIT1
#define RED_LED BIT0
#define DEBOUNCE_DELAY 6400000
#define BUTTON_1_RELEASED (P1IN & BUTTON_1)
#define BUTTON_1_PRESSED (!BUTTON_1_RELEASED)

void setupStartStop() {
	P1DIR &= ~BUTTON_1;	//Button is an input
	P1DIR |= RED_LED;	// Stop sign
	P1OUT &= ~RED_LED;	// Clear the red.
	P1OUT |= BUTTON_1;	// Button has pull up resistor
	P1REN |= BUTTON_1;	// Setup the pull up
	P1IES &= ~BUTTON_1;	// On the falling edge
	P1IE |= BUTTON_1;	// Turn on interrupts for the button
}

#pragma vector = PORT1_VECTOR
__interrupt void startStopISR() {
	if(P1IFG & BUTTON_1) {
		TA0CCR1 = 0;
		TA0CCR2 = 0;
		TA2CCR1 = 0;
		TA2CCR2 = 0;
		// Button 1 is being pressed. Debounce it first
		__delay_cycles(DEBOUNCE_DELAY); // 1/4 of a second
		
		//Check if it is still pressed.
		if(BUTTON_1_PRESSED) {
			while(BUTTON_1_PRESSED) {
				// Wait to be released
			}
			// Released!
			__delay_cycles(DEBOUNCE_DELAY); // 1/4 of a second debounce
			// Ok, check if is properly released.
			if(BUTTON_1_RELEASED) {
				// OK!! LET'S STOP EVERYTHING!
				P1OUT |= RED_LED;
				// Remember, GIE is already off, so we don't need to stop that.
				while(BUTTON_1_RELEASED) {
					TA0CCR1 = 0;
					TA0CCR2 = 0;
					TA2CCR1 = 0;
					TA2CCR2 = 0;
				}
				// Maybe the button is being pressed again! Time to start again?
				__delay_cycles(DEBOUNCE_DELAY); // 1/4 of a second debounce
				if(BUTTON_1_PRESSED) {
					// Ok, it was really pressed.
					// Time to turn on!
					P1OUT &= ~RED_LED;
					P1IFG &= ~BUTTON_1;	// Time to clean up and get outta here.
				}
			}
		}
	}
	P1IFG &= ~BUTTON_1;	// Time to cleaned up and get outta here.	
}
