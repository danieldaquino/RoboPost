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

#define SCLKDIV 50
char txData;
extern unsigned char mstData, slvData;
void ucsiB1SpiInit(unsigned int sclkDiv);
void ucsiB1SpiClkDiv(unsigned int sclkDiv);
void spiTx_RxByte(char *txData,char *rxData,char NUM_DATA);

#endif /* UCSISPI_H_ */
