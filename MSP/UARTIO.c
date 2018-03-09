/*===============================

	UART IO
	
	this C module is part of the MSP Motor Control.
	It provides functions that allow you to communicate with your computer.
	
	Written by Daniel Walnut
	
	Requirements for use:
	
	Make sure you have GLOBAL INTERRUPTS ENABLED! OTHERWISE IT WILL NOT WORK
	
	This module will use UCSI_A1. Beware of other modules using the same module.
	Also, this will use P4.4, AND P4.5. Please do not interfere with them.
	
	For function descriptions and usage, please refer to UARTIO.h	

===============================*/

#include <msp430.h>
#include "UARTIO.h"


#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:
	//No interrupt pending... How did you get here?  
	break;
  case 2:
	// RX received something. Go get it
	// get it at UCA1RXBUF
    break;
  case 4:
    	//TX buffer is empty! let's write to it
		if(strBufferToSend[strBufferPointer] == '\0' || strBufferPointer >= 30) {
			//Done sending big buffer
			strBufferPointer = 0; // Pointer at beginning
			strBufferReady = 1; // We are ready for more.
		}
		else if(strBufferReady != 1) {
			//Let's send the next one in line.
			UCA1TXBUF = strBufferToSend[strBufferPointer];
			strBufferPointer++;
		}
    break;
  default: break;
  }
}

char UARTIOSend(unsigned char *txBuffer) {
	if(strBufferReady) {
		//Ok, setup everything for sending away...
		strcpy(strBufferToSend, txBuffer);
		strBufferReady = 0; // We are busy
		strBufferPointer = 0; // Point to the beginning of the string.
		UCA1TXBUF = strBufferToSend[strBufferPointer]; //Let's send the first bit.
		strBufferPointer++; // Move to next character in line
		return 0;
	}
	else {
		//We are busy... REJECT
		return -1;
	}
}

void UARTIOInit() {

	// Reset String buffer, pointer and ready signal
	int i;
	for(i=0;i < STR_BUFFER_SIZE;i++) {
		strBufferToSend[i] = 0x00; // Empty buffer
	}
	strBufferPointer = 0; // Pointer at beginning

	P4SEL |= BIT4 | BIT5; // Select Pins 4.4 and 4.5 for UART communication.
	UCA1CTL1 |= UCSWRST; // Stop the UCSI state machine for configuration.
	
	// DO NOT CONFIGURE UCSI A1 OUTSIDE THESE REMARKS ****
	//********************
	UCA1CTL1 |= UCSSEL_2; 		// select SMCLK. 1MHz

	UCA1CTL0  = 0; // reset configuration
	UCA1CTL0 &=	~UCPEN  // No Parity
			 &	~UCMSB  // LSB First
			 &	~UC7BIT // 8 bits of data
			 &	~UCSPB	// 1 stop bit
			 &	~UCSYNC;// UART Mode


	UCA1BR0 = 3; // Setting system to 19200bps. Refer to table at "36.3.13 Typical Baud Rates and Errors" - Document SLAU208O
	UCA1BR1 = 0; // Setting system to 19200bps. Refer to table at "36.3.13 Typical Baud Rates and Errors" - Document SLAU208O
	UCA1MCTL = UCBRF_6 | UCBRS_1 | UCOS16; // Setting system to 19200bps. Refer to table at "36.3.13 Typical Baud Rates and Errors" - Document SLAU208O
	//********************

	UCA1CTL1 &= ~UCSWRST; //  configured. take state machine out of reset.

	UCA1IE |= UCTXIE; //Enable interrupts for Tx
	//UCRXIE?
	
	strBufferReady = 1; //We are ready to receive TX requests
}

