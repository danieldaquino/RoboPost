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
	2. Dual Motor Controller Module
	3. LineSensorDriver
	4. Dual Velocity Gauge
	5. Line Cruiser
	6. Start Stop module
	
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
#define NUM_PARAM 12

/*=======
Globals
========*/
float DataArray[NUM_PARAM];
float CommandArray[NUM_PARAM];
uint32_t Color;
float Desired_Speed;

/*======
~~InfoBoardUpdate~~

Simultaneously receive parameters, and send the measurements, listed in an InfoBoard.

inputs:
	(float *) DataArray: Measurement data being sent to the Photon.
	(float *) CommandArray: Parameter command data being received
outputs: none

======*/
void InfoBoardUpdate();

#endif
