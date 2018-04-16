/*===============================

	# DataErrorCheck
	
	This module allows you to check the integrity of transmitted information,
	by using a Cyclic Redundancy Check algorithm.
	
	For more information, please refer to DataErrorCheck.h
			
===============================*/
/*=======
Includes
========*/
#include "DataErrorCheck.h" 

/*=======
Static Variables
========*/
// A table of pre calculated values to aid in computation
unsigned char CRCTable[256];

/*=======
Static Function Prototypes
========*/

/*======
~~ getCRCForByte ~~

Gets the binary polynomial remainder in division val / CRC_POLY

inputs:
	(unsigned char) val: The value in the dividend. LSB first.
outputs: 
	(unsigned char) CRC code: The remainder of val / CRC_POLY
Globals affected: none
======*/
static unsigned char getCRCForByte(unsigned char val);

/*=======
Functions
========*/


static unsigned char getCRCForByte(unsigned char val) {
	unsigned char j;

	for (j = 0; j < 8; j++) {
		if (val & 1) {
			// If MSB is 1, then subtract from the scaled CRC_POLY 
			val ^= CRC_POLY;
		}
		// Move on to the next MSB
		val >>= 1;
	}
	// Return remainder
	return val;
}
 
void dataErrorCheckInit()
{
	int i;
	// fill an array with CRC values of all 256 possible bytes
	for (i = 0; i < 256; i++)
	{
		CRCTable[i] = getCRCForByte(i);
	}
}
 
void stampMessage(unsigned char * message, int length) {
	int i;
	unsigned char crc = 0;
	// Calculate the CRC checksum code...
	for (i = 0; i < length - 1; i++) {
		crc = CRCTable[crc ^ message[i]];
	}
	
	// Stamp the last code
	message[length - 1] = crc;
}

unsigned char checkDataError(unsigned char * message, int length) {
	int i;
	unsigned char crc = 0;
	// Calculate the CRC checksum code...
	for (i = 0; i < length; i++) {
		crc = CRCTable[crc ^ message[i]];
	}
	return crc;
}
 
