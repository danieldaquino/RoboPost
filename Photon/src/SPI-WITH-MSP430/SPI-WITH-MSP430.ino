    
/*======================

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
float sendValues[NUM_PARAM];
float rcvdValues[NUM_PARAM];
unsigned char command[NUM_PARAM];

void SPIMSPSetup() {
	// Initialize Serial port
	Serial.begin(9600);
	while (!Serial) continue;
	
    SPI.onSelect(slaveSelect);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin(SPI_MODE_SLAVE, SS_PIN);
}

void SPIMSPLoop() {
    if (gotValue) {
		//transfer complete flag set do something if you need to
		ReceiveInfoBoard();
		FillInfoBoard();
		timeStamp = millis();
		gotValue = false;
	}
}

void FillInfoBoard() {
	int i;
	i = 0;
	sendValues[i] = robotPlay; //  A 1 indicates the robot has to start running. A 0 indicates a stop signal.
	i++;
	sendValues[i] = sharpestCurve; // Tightest curve radius in cm
	i++;
	sendValues[i] = cruiseKp; // Proportional gain of the lineCruiser
	i++;
	sendValues[i] = cruiseKd; // Differential gain of the lineCruiser
	i++;
	sendValues[i] = corneringDBrakeFactor; // Number between 0 and 1 to tell how much to slow down in tightening curves. 0 means never slows down. 1 means full stop on tightest curve.
	i++;
	sendValues[i] = corneringPBrakeFactor; // Number between 0 and 1 to tell how much to slow down in a given curve. 0 means never slows down. 1 means full stop on tightest curve.
	i++;
	sendValues[i] = motorKp; // Proportional gain of the motors.
	i++;
	sendValues[i] = motorKd; // Differential gain of the motors.
	i++;
	sendValues[i] = Desired_Speed;	//desired speed
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
	i++;
	Color = rcvdValues[i];		//color reading from msp
}

void slaveSelect(uint8_t state) {
	// We were selected!
    if (state) {
    	// Let's transfer those bytes!
        SPI.transfer(sendValues, rcvdValues, sizeof(float)*NUM_PARAM, slaveCallback);
    }
}

void slaveCallback() {
	// Alright! Transfer is complete
    gotValue = true;
}
