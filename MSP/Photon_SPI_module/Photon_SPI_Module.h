/*===============================

	# Photon SPI Module
	
	This module allows you to update robot parameters, 
	and send current measurements to Photon over SPI.
	
	## Resources used (by this and its children):

	- UCSIB1: to perform data transfer over SPI
 	- P4.1: MOSI
 	- P4.2: MISO
 	- P4.3: SCLK
 	- P6.5: SS
	
	
	# Requirements
	
	1. ucsiSpi Module
	
	# Wiring with Photon
	
	P4.1 MOSI-->A5
	P4.2 MISO-->A4
	P4.3 SCLK-->A3
    P6.5 SS-->A2
    
    GND --> GND
	
===============================*/
#ifndef PHOTON_SPI_MODULE_H
#define PHOTON_SPI_MODULE_H

#include <stdint.h>

/*=======
Macros
========*/
// Number of parameters inside the Infoboard array
#define NUM_PARAM 11

/*=======
Globals
========*/
char robotPlay;
char sharpestCurve;
float cruiseKp;
float cruiseKd;
float corneringDBrakeFactor;
float corneringPBrakeFactor;
float motorKp;
float motorKd;


/*======
~~InfoBoardUpdate~~

Simultaneously receive parameters, and send the measurements, listed in an InfoBoard.

inputs:
	(float *) DataArray: Measurement data being sent to the Photon.
	(float *) CommandArray: Parameter command data being received
outputs: none

======*/
void InfoBoardUpdate(float *DataArray,float *CommandArray);

/*======
~~InfoBoardFill~~

Fills Info Board with measurements according to Info Board requirements

inputs: none
outputs: none

======*/
void InfoBoardFill();

#endif
