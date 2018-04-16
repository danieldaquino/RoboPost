/*===============================

	# DataErrorCheck
	
	This module allows you to check the integrity of transmitted information,
	by using a Cyclic Redundancy Check algorithm.
	
	based on a Pololu sample code (https://www.pololu.com/docs/0J44/6.7.6)
			
===============================*/
#ifndef DATA_ERROR_CHECK_H
#define DATA_ERROR_CHECK_H

/*=======
Macros
========*/
// Polynomial to become the divisor in the CRC algorithm. Make sure this matches on your receiver/transmitter
// LSB first.
#define CRC_POLY 0x73


/*=======
Function prototypes
========*/

/*======
~~ dataErrorCheckInit ~~

Initializes the dataErrorCheck. Builds the CRC table.

inputs: none
outputs: none
Globals affected: none
======*/
void dataErrorCheckInit();

/*======
~~ stampMessage ~~

Stamps the Error Check Code on the message

inputs: 
	(unsigned char *) message: The message to be stamped.
	Make sure to leave last byte empty, as it will be overwritten with the stamp
	(int) length: The length of message.
	
outputs: none. However, last byte of message will be overwritten. Make sure there is no info.
Globals affected: none
======*/
void stampMessage(unsigned char * message, int length);

/*======
~~ checkDataError ~~

reads the Error Check code stamp, calculate the stamp, and checks if there was an error

inputs: 
	(unsigned char *) message: The message to be checked.
	(int) length: The length of message.
	
outputs: 
	(unsigned char) Error status: 0 means no error, any other means error.
	
Globals affected: none
======*/
unsigned char checkDataError(unsigned char * message, int length);

#endif