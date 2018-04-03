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
/*=======
Globals
========*/
#define NUM_PARAM 10
uint32_t sendValues[NUM_PARAM];
uint32_t rcvdValues[NUM_PARAM];
unsigned char command[NUM_PARAM];

void SPIMSPSetup() {
	// Initialize Serial port
	Serial.begin(9600);
	while (!Serial) continue;
	
	sendValues[0] = 0x00100000;
	sendValues[1] = 0x00200000;
	sendValues[2] = 0x00400000;
	sendValues[3] = 0x00800000;
	sendValues[4] = 0x01000000;
	sendValues[5] = 0x02000000;
	sendValues[6] = 0x04000000;
	sendValues[7] = 0x08000000;
	sendValues[8] = 0x10000000;
	sendValues[9] = 0x20000000;
    SPI.onSelect(slaveSelect);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin(SPI_MODE_SLAVE, SS_PIN);
}

void SPIMSPLoop() {
    if (gotValue) {
		//transfer complete flag set do something if you need to
		ReceiveInfoBoard();
		gotValue = false;
	}
}

void ReceiveInfoBoard() {
	int i;
	i = 0;
	RPMLS = rcvdValues[i];				// RPMLS: Left RPM Setpoint
	i++;
	RPML = rcvdValues[i];					// RPML: Left RPM
	i++;
	RPMRS = rcvdValues[i];				// RPMRS: Right RPM Setpoint
	i++;
	RPMR = rcvdValues[i];					// RPMR: Right RPM
	i++;
	TA0CCR0_REG = rcvdValues[i];			// Left PWM Frequency register
	i++;
	TA0CCR1_REG = rcvdValues[i];			// Left PWM Frequency Forward duty cycle register
	i++;
	TA0CCR2_REG = rcvdValues[i];			// Left PWM Frequency Reverse duty cycle register
	i++;
	TA2CCR0_REG = rcvdValues[i];			// Right PWM Frequency register
	i++;
	TA2CCR1_REG = rcvdValues[i];			// Right PWM Frequency Forward duty cycle register
	i++;
	TA2CCR2_REG = rcvdValues[i];			// Right PWM Frequency Reverse duty cycle register
	i++;
	lastSensorPosition = rcvdValues[i];	// sensor: Sensor data (-1 - +1)
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
