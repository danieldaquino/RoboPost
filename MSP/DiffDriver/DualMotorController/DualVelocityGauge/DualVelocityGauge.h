/*===============================

	# Dual Velocity Gauge

	This module gathers signals from an encoder, counts the pulses,
	and it estimates the velocity.
	
	## Resources Used
	
	1. P2.0 for the Motor-1 Encoder
	2. P2.2 for the Motor-2 Encoder
	3. Timer A1 to setup the Velocity Calculations.
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	## Modifying
	
	1. Use Port 1 or 2 for Encoders. They need to be interrupt enabled pins.
	2. Use the same Port for both Encoders. Otherwise significant changes to code will have to be made
	3. Modify the switch structure in encoderISR if you change the pins

===============================*/
#ifndef DUAL_VELOCITY_GAUGE_H
#define DUAL_VELOCITY_GAUGE_H

/*=======
Includes
========*/
#include <msp430.h>

/*=======
Macros
========*/
#define P_ENCODER_OUT P2OUT
#define P_ENCODER_DIR P2DIR
#define P_ENCODER_IN P2IN
#define P_ENCODER_IE P2IE
#define P_ENCODER_IFG P2IFG
#define P_ENCODER_IV P2IV
#define P_ENCODER_REN P2REN
#define P_ENCODER_VECTOR PORT2_VECTOR

#define ENCODER_1 BIT0
#define ENCODER_2 BIT2
#define ENCODERS (ENCODER_1 | ENCODER_2)

#define COUNTS_PER_REV 11.0
#define GEAR_RATIO 20.4

/*=======
Globals
=======*/

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

returns the RPM speed of gearmotor.
ATTENTION: THIS FUNCTION CANNOT TELL THE DIFFERENCE BETWEEN DIRECTIONS!!

inputs: 
	(char) motor to be selected. either 1 or 2 please.
outputs: 
	(double) Velocity of gearmotor shaft, in RPM.
Globals affected: none
======*/
float getRPM(char motor);

#endif