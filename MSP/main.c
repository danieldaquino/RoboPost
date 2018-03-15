#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UARTIO/UARTIO.h"
#include "DiffDriver/DiffDriver.h"
#include "DiffDriver/DualMotorController/DualMotorController.h"
#include "Scheduler/Scheduler.h"
#include "I2CModule/I2CModule.h"
#include "LineSensorDriver/LineSensorDriver.h"
#include "CPUClock/CPUClock.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Setup the CPU rate. MUST BE DONE BEFORE the other modules.
	boostClockTo16MHz();
	
	// Setup scheduler before the diff driver!!
	schedulerInit();
	diffDriverInit();
	UARTIOInit(); // Initialize communication with Computer Console
	lineSensorInit();

	int sen[10];
	char status_UART;
	char reading;
	
	__enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
	
	// Let's get this party started
	// Go straight at 60cm/s
	diffDrive(60, 10000);
	while(1) {
		//Nothing yet
		char LeString[60];
		reading=LSRead();
		int strSize;
		strSize = sprintf(LeString, "sensor:%d | 1: %d RPM | 2: %d RPM | S: %d cm/s | R: %d cm\n\r", reading, (int) getRPM(1), (int) getRPM(2), (int) getSpeed(), (int) getCurveRadius());
		UARTIOSend(LeString, strSize);
		__delay_cycles(100000);
	}
	return 0;
}
