/*===============================

	Velocity Gauge
	
	this C module is part of the MSP Motor Control.
	It gathers signals from and encoder, counts the pulses,
	and it estimates the velocity.
	
	Requirements for use:
	
	P1.3 must be connected to a motor encoder channel
	This module will modify P1.3, so do not use any other modules that use it.
	
	Note:If you want to use another pin, modify the Macros as well as the ISR. Make sure to use an
	interrupt enabled port like P1 or P2
	
	For function descriptions and usage, please visit VelocityGauge.h

===============================*/

/*=======
Includes
=======*/
#include <msp430.h>
#include "DualVelocityGauge.h"

/*=======
Statics
=======*/
static long int encoder1Count;
static long int enc1CountsIn100ms;
static long int encoder2Count;
static long int enc2CountsIn100ms;

//To do: Create shared port ISR driver module
#pragma vector=P_ENCODER_VECTOR
__interrupt void encoderISR(void) {
	switch(__even_in_range(P_ENCODER_IV,8)) {
		case 0x0:
			//Nothing. How did we end up here?
			break;
		case 0x02:
			//P2.0 - Encoder 1
			encoder1Count++; //Increase count
			break;
		case 0x04:
			//P2.1 - Not interested
			break;
		case 0x06:
			//P2.2 - Encoder 2
			encoder2Count++; //Increase count
			break;
		case 0x08:
			//P2.3 - Not interested
			break;
		default:
			//Nothing here
			break;
	}
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void velocityTimerISR(void) {

	enc1CountsIn100ms = encoder1Count; // Get encoder 1 count
	encoder1Count = 0; // Reset encoder count
	
	enc2CountsIn100ms = encoder2Count; // Get encoder 2 count
	encoder2Count = 0;
	
	TA1CTL &= ~TAIFG; // Clear interrupt flag
}

float getRPM(char motor) {
	if(motor == 1) {
		return (60*((double) enc1CountsIn100ms*10)/COUNTS_PER_REV)/GEAR_RATIO;
	}
	else if(motor == 2) {
		return (60*((double) enc2CountsIn100ms*10)/COUNTS_PER_REV)/GEAR_RATIO;		
	}
	else {
		return 0;
	}
}

void velocityGaugeInit(void) {
	//Setup pins
	P_ENCODER_DIR &= ~ENCODERS; //Encoder is an input
	P_ENCODER_IE |= ENCODERS; //Enable interrupts for encoder
	P_ENCODER_REN |= ENCODERS; //Enable Pull up/down resistor
	P_ENCODER_OUT &= ~ENCODERS; // Pull down resistor
	
	//Setup TimerA1 for velocity measurements
	// TASSEL_1: ACLK = 32KHz
	// ID_3: Divide by 8. We are at 4KHz
	// MC_1: Up mode. Counts to TA1CCR0
	TA1CTL = TASSEL_1 | ID_3 | MC_1 | TAIE;
	TA1CTL &= ~TAIFG; //Clear interrupts
	TA1CCR0 = 400; // Make interrupts happen at 10Hz
}
