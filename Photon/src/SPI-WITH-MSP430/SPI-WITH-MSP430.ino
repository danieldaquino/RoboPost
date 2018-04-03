/*=======================

# SPI-WITH-MSP430.ino

Forked from Jeremy Ellis (MIT license)
Modified by: Tim Yue

Use at your own risk!?

# MSP430F5529 to Photon SPI Setup

	GND to GND
	P6.5 to A2   SS
	P4.3 to A3   SCK
	P4.2 to A4   MISO
	P4.1 to A5   MOSI
========================*/
/*=======
Includes
========*/
#include "SPI-WITH-MSP430.h"

/*=======
Function prototypes
========*/
void slaveSelect(uint8_t state);
void slaveCallback();

/*=======
Globals
========*/
const int SS_PIN = A2;
bool gotValue = false;

void SPIMSPSetup() {
	// Initialize Serial port
	Serial.begin(9600);
	while (!Serial) continue;
	sendValues[0] = 'P';
	sendValues[1] = 'H';
	sendValues[2] = 'O';
	sendValues[3] = 'T';
	sendValues[4] = 'O';
	sendValues[5] = 'N';
	sendValues[6] = '!';
	sendValues[7] = 'F';
	sendValues[8] = 'T';
	sendValues[9] = 'W';
    SPI.onSelect(slaveSelect);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin(SPI_MODE_SLAVE, SS_PIN);
}

void SPIMSPLoop() {
    if (gotValue) {
		//transfer complete flag set do something if you need to
		printReceivedToSerial();
		gotValue = false;
	}
}

void printReceivedToSerial() {
	Serial.println("Incoming!");
	for(int i=0;i < NUM_PARAM;i++) { 
		Serial.println(rcvdValues[i]);
	}
}

void slaveSelect(uint8_t state) {
	// We were selected!
    if (state) {
    	// Let's transfer those bytes!
        SPI.transfer(sendValues, rcvdValues, sizeof(uint32_t)*NUM_PARAM, slaveCallback);
    }
}

void slaveCallback() {
	// Alright! Transfer is complete
    gotValue = true;
}
