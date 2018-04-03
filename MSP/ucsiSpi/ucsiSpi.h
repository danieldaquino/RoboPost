/*
 * ucsiSpi.h
 *
 *  Created on: Feb 19, 2017
 *      Author: Greg Scutt
 *      modified by: Tim Yue on APR 1ST 2018
 *
 *      this module occupies UCSIB1 to perform data transfer over SPI
 *      used pins:
 *      - P4.1:MOSI
 *      - P4.2:MISO
 *      - P4.3:SCLK
 *      - P6.5:SS
 */
#ifndef UCSISPI_H_
#define UCSISPI_H_

/*=======
Macros
========*/
#define SCLKDIV 50
// Slave Select parameters
#define P_SS_OUT P6OUT
#define P_SS_DIR P6DIR
#define SS BIT5

#define P_SPI_OUT P4OUT
#define P_SPI_DIR P4DIR
#define P_SPI_SEL P4SEL
#define MOSI BIT1
#define MISO BIT2
#define SCLK BIT3

/*=======
Globals
========*/
char txData;
extern unsigned char mstData, slvData;

/*=======
Functions
========*/

/*======
~~ucsiB1SpiInit~~

Initializes SPI module

inputs:
	(unsigned int) sclkDiv: How many times the SMCLK frequency should be divided.
outputs: none

======*/
void ucsiB1SpiInit(unsigned int sclkDiv);

/*======
~~ucsiB1SpiClkDiv~~

Changes the SMCLK division scale.

inputs:
	(unsigned int) sclkDiv: How many times the SMCLK frequency should be divided.
outputs: none

======*/
void ucsiB1SpiClkDiv(unsigned int sclkDiv);

/*======
~~spiTx_RxByte~~

Sends and receives multiple bytes at the same time.

inputs:
	(char *) txData: The pointer to the byte to be transmitted
	(char *) rxData: The pointer to the byte to be transmitted
	(char) numData: 
outputs: none
======*/
void spiTx_RxBytes(char *txData,char *rxData,char numData);

/*======
~~slaveSelect~~

Selects slave. Should be called before doing SPI transfers

inputs: none
outputs: none
======*/
inline void slaveSelect();

/*======
~~slaveDeselect~~

Deselects slave. Should be called after doing SPI transfers

inputs: none
outputs: none
======*/
inline void slaveDeselect();

#endif /* UCSISPI_H_ */
