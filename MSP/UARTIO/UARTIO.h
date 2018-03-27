/*===============================

	UART IO
	
	this C module is part of the MSP Motor Control.
	It provides functions that allow you to communicate with your computer.
	
	Written by Daniel Walnut
	
	Requirements for use:
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	This module will use UCSI_A1. Beware of other modules using the same module.
	Also, this will use P4.4, AND P4.5. Please do not interfere with them.
	

===============================*/

#ifndef UARTIO_H_
#define UARTIO_H_

/*=======
Macros
========*/
#define STR_BUFFER_SIZE 150

/*=======
Globals
=======*/
char strBufferToSend[STR_BUFFER_SIZE];
char strBufferPointer;
unsigned char strBufferReady;


/*=======
Function Prototypes
========*/

/*======
~~UARTIOInit~~

This function will initialize the UCSI_A1 module as UART, as well as TXD/RXD connection with 
the USB channel

inputs: none
outputs: none
Globals affected: UCSI_A1 module, P4.4, P4.5
=======*/
void UARTIOInit();

/*======
~~UARTSend~~

This function will send a string to the computer.

inputs: 
	(char*) txBuffer: String to send, should be of maximum size STR_BUFFER_SIZE.
						If string is larger than that, function will return -2
	(int) size: size of the string, NOT INCLUDING NULL CHARACTER 
outputs: 
	(char) Return status:	 0 means successful.
					 		-1 means busy, try again later.
					 		-2 means overflow.
					 		-3 means it is missing a null character at the end.
Globals affected: strBufferToSend, strBufferPointer, strBufferReady
=======*/
char UARTIOSend(unsigned char *txBuffer, int size);

/*======
~~USCI_A1_ISR~~

This function will handle the nitty gritty of sending each byte.
inputs: none
outputs: none
Globals affected: strBufferToSend, strBufferPointer, strBufferReady
=======*/
void USCI_A1_ISR(void);

#endif
