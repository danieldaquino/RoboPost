#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UARTIO.h"
#include "DiffDriver/DiffDriver.h"
#include "DiffDriver/DualMotorController/DualMotorController.h"
#include "Scheduler/Scheduler.h"
#include "I2C_modual.h"

#define SETPOINT 230.0
#define SETPOINT2 230.0

/**
 * main func robopost.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Setup scheduler before the diff driver!!
	schedulerInit();
	diffDriverInit();
	UARTIOInit(); // Initialize communication with Computer Console
	LineSensorinit();

	int sen[10];
	char status_UART;
	char reading;
	
	__enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
	
	// Let's get this party started
	// Go at 40cm/s 
	//diffDrive(40, 10000);	
	setRPM(1, 90);
	setRPM(2, 250);
	while(1) {
		//Nothing yet
		char LeString[60];
		reading=LSRead();
		sprintf(LeString, "sensor:%d | 1: %d RPM | 2: %d RPM | S: %d cm/s | R: %d cm\n\r", reading, (int) getRPM(1), (int) getRPM(2), (int) getSpeed(), (int) getCurveRadius());
		UARTIOSend(LeString);
		__delay_cycles(100000);
	}
	return 0;
}
