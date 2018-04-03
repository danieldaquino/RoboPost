/*
 * ucsiSpi.c
 *
 *  Created on: Feb 19, 2017
 *      Author: Greg Scutt
 *      modified by: Tim Yue on APR 1ST 2018
 *
 *	For more information and usage, please refer to ucsiSpi.h
 *
 */
/*=======
Includes
========*/
#include <msp430.h>
#include "ucsiSpi.h"
#include <stdint.h>


/*=======
Macros
========*/
#define TRANSMIT_READY (UCB1IFG & UCTXIFG)
#define RECEIVE_READY (UCB1IFG & UCRXIFG)

void ucsiB1SpiInit(unsigned int sclkDiv){

    UCB1CTL1 |= UCSWRST;                        // **Put state machine in USCI reset to intitialize it**

    UCB1CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;      // 3-pin, 8-bit SPI master
                                                // Clock polarity high, MSB
    UCB1CTL1 |= UCSSEL_2;                       // SMCLK is source
    UCB1BR0 = (sclkDiv&0xFF);                   // divide SMCLK by sclkDiv
    UCB1BR1 = (sclkDiv>>8);                     //
    //UCB1STAT &=~ UCLISTEN;

    UCB1CTL1 &= ~UCSWRST;                       // **Initialize USCI state machine**
    
	// Initialize the SPI pins
    P_SPI_SEL |= MOSI | MISO | SCLK;
	P_SS_OUT |= SS;	// Normally high
	P_SS_DIR |= SS;	// Output
}

void ucsiB1SpiClkDiv(unsigned int sclkDiv){

    UCB1CTL1 |= UCSWRST;            // you always need to put state machine into reset when configuring UCSC

    UCB1BR0 = (sclkDiv&0xFF);                   // 2
    UCB1BR1 = (sclkDiv>>8);                     //

    UCB1CTL1 &= ~UCSWRST;                       // **Initialize USCI state machine**
}

void spiTx_RXBytes(char *txData,char *rxData,char numData)
{
    int i;
    for(i = 0;i < numData*sizeof(uint32_t); i++) {  	
		// transmit a byte on SPI if it is ready !!
		while(!TRANSMIT_READY);		// Wait until we are ready
		
		__delay_cycles(100);
        UCB1TXBUF = *(txData+i);	//SHOVE IT IN to the transmit Buffer
        
    	while(!RECEIVE_READY);		// wait for transaction to complete
    	
        *(rxData+i) = UCB1RXBUF;	// grab and run
        
        UCB1IFG &= ~UCRXIFG;		// Clear the flag.
	}
}

inline void slaveSelect() {
	P_SS_OUT &= ~SS;       // select the device
}

inline void slaveDeselect() {
	P_SS_OUT |= SS;    // deselect device
}
