#include <msp430.h> 
#include <stdio.h>

#include "UARTIO.h"
#include "DiffDriver/DiffDriver.h"
#include "DiffDriver/DualMotorController/DualMotorController.h"
#include "Scheduler/Scheduler.h"

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
	
	__enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
	
	// Let's get this party started
	// Go at 40cm/s, 40cm
	diffDrive(60, -20);
	while(1) {
		//Nothing yet
		char LeString[60];
		sprintf(LeString, "1: %d RPM | 2: %d RPM | S: %d cm/s | R: %d cm\n\r", (int) getRPM(1), (int) getRPM(2), (int) getSpeed(), (int) getCurveRadius());
		UARTIOSend(LeString);
		__delay_cycles(100000);
	}
	return 0;
}
