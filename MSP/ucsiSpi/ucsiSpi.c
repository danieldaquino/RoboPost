/*
 * ucsiSpi.c
 *
 *  Created on: Feb 19, 2017
 *      Author: Greg Scutt
 *      modified by: Tim Yue on APR 1ST 2018
 *
 *
 */

#include <msp430.h>
#include "ucsiSpi.h"
#include <stdint.h>


// these functions could be made more generic with the driver lib functions
void ucsiB1SpiInit(unsigned int sclkDiv){

    UCB1CTL1 |= UCSWRST;                        // **Put state machine in USCI reset to intitialize it**

    UCB1CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;      // 3-pin, 8-bit SPI master
                                                // Clock polarity high, MSB
    UCB1CTL1 |= UCSSEL_2;                       // SMCLK is source
    UCB1BR0 = (sclkDiv&0xFF);                   // divide SMCLK by sclkDiv
    UCB1BR1 = (sclkDiv>>8);                     //
    //UCB1STAT &=~ UCLISTEN;


    UCB1CTL1 &= ~UCSWRST;                       // **Initialize USCI state machine**
    P4SEL|=BIT1|BIT3|BIT2;  //BIT1=MOSI-->A5|BIT2=MISO-->A4|BIT3=SCLK-->A3
    P6OUT|=BIT5;        //SS-->A2
        P6DIR|=BIT5;
    //UCB1TXBUF=0X80;
}



void ucsiB1SpiClkDiv(unsigned int sclkDiv){

    UCB1CTL1 |= UCSWRST;            // you always need to put state machine into reset when configuring UCSC

    UCB1BR0 = (sclkDiv&0xFF);                   // 2
    UCB1BR1 = (sclkDiv>>8);                     //


    UCB1CTL1 &= ~UCSWRST;                       // **Initialize USCI state machine**
}


/************************************************************************************
* Function: spiTx_RXByte
* - if TXBUFFER is ready!!  then a byte is written to buffer and serialized on SPI UCB1. nothing else happens.
* argument:
*   *txData - character to be serialized over SPI
*   *RxData - byte from photon
*   NUM_DATA -NUM of element needed to be transfered
*
* return: none
* Author: Tim
* Date: APR 1ST, 2018
************************************************************************************/
void spiTx_RXByte(char *txData,char *rxData,char NUM_DATA)
{

    int i=0;

    while(i<NUM_DATA*sizeof(uint32_t))
    { // transmit a byte on SPI if it is ready !!
    while(!(UCB1IFG&UCTXIFG));
    __delay_cycles(100);
        UCB1TXBUF=*(txData+i);   //SHOVE IT IN to the transmit Buffer
        //__delay_cycles(1000);
    while(!(UCB1IFG&UCRXIFG));  // wait for transaction to complete
        *(rxData+i)=UCB1RXBUF;   // garb and run
        UCB1IFG&=~UCRXIFG;
        i++;}

}

