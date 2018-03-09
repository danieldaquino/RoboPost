#ifndef VELOCITY_GAUGE_H
#define VELOCITY_GAUGE_H

#include <msp430.h>

/*===============================

	Velocity Gauge
	
	this C module is part of the MSP Motor Control.
	It gathers signals from and encoder, counts the pulses,
	and it estimates the velocity.
	
	Written by Daniel Walnut
	
	Requirements for use:
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	P1.3 must be connected to a motor encoder channel
	This module will modify P1.3, so do not use any other modules that use it.
	This module will also modify Timer A1. Beware.
	
	Note:If you want to use another pins, modify the Macros. Make sure to use an
	interrupt enabled port like P1 or P2

===============================*/

/*=======
Macros
========*/
#define P_ENCODER_OUT P1OUT
#define P_ENCODER_DIR P1DIR
#define P_ENCODER_IN P1IN
#define P_ENCODER_IE P1IE
#define P_ENCODER_IFG P1IFG
#define P_ENCODER_IV P1IV
#define P_ENCODER_REN P1REN

#define ENCODER_BIT BIT3

#define COUNTS_PER_REV 11.0
#define GEAR_RATIO 20.4

/*=======
Globals
=======*/
long int encoderCount;
long int countsIn100ms;

/*=======
Function Prototypes
========*/

/*======
~~encoderISR~~

This function will be the one responsible for counting pulses
inputs: none
outputs: none
Globals affected: encoderCounts
=======*/
void encoderISR(void);

/*======
~~velocityTimerISR~~

This function will record the number of counts within 100ms (or the Timer A setting)
inputs: none
outputs: none
Globals affected: encoderCounts, countsIn100ms
=======*/
void velocityTimerISR(void);

/*======
~~velocityGaugeInit~~

This function initializes all parameters necessary
inputs: none
outputs: none
Globals affected: Encoder pin (usually P1.3), Timer A1 configurations
======*/
void velocityGaugeInit(void);

/*======
~~getRPM~~

returns the RPM speed of gearmotor

inputs: none
outputs: 
	(double) Velocity of gearmotor shaft, in RPM.
Globals affected: none
======*/
float getRPM(void);

#endif