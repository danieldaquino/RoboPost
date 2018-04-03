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
	
===============================*/
#ifndef PHOTON_SPI_MODULE_H
#define PHOTON_SPI_MODULE_H


/*=======
Macros
========*/
// Number of parameters inside the Infoboard array
#define NUM_PARAM 11

/*======
~~InfoBoardUpdate~~

Simultaneously receive parameters, and send the measurements, listed in an InfoBoard.

inputs:
	(int *) DataArray: Measurement data being sent to the Photon.
	(int *) CommandArray: Parameter command data being received
outputs: none

======*/
void InfoBoardUpdate(int *DataArray,int *CommandArray);

/*======
~~InfoBoardInit~~

Initializes infoboard

inputs:
	(int *) DataArray: Measurement data being sent to the Photon.
	(int *) CommandArray: Parameter command data being received
outputs: none

======*/
void InfoBoardInit(int *DataArray,int *CommandArray);

#endif
