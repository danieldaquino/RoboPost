/*=======================

# SPI-WITH-MSP430 module

Forked from Jeremy Ellis (MIT license)
Modified by: Tim Yue

Use at your own risk!?

# MSP430F5529 to Photon SPI Setup

	GND to GND
	P6.5 to A2   SS
	P4.3 to A3   SCK
	P4.2 to A4   MISO
	P4.1 to A5   MOSI
========================*/
#ifndef SPIMSP_H
#define SPIMSP_H

/*=======
Globals
========*/
#define NUM_PARAM 10
uint32_t sendValues[NUM_PARAM];
uint32_t rcvdValues[NUM_PARAM];
unsigned char command[NUM_PARAM];

/*=======
Function prototypes
========*/

/*======
~~SPIMSPLoop~~

Loop of this module

inputs: none
outputs: none
======*/
void SPIMSPLoop();

/*======
~~SPIMSPSetup~~

Setup this module

inputs: none
outputs: none

======*/
void SPIMSPSetup();


#endif