#include <msp430.h> 
#include <stdio.h>

#include "UARTIO.h"
#include "DiffDriver/DualMotorController/DualMotorController.h"


#define SETPOINT 300.0
#define SETPOINT2 200.0
/**
 * main func robopost.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	motorControllerInit();	
	UARTIOInit(); // Initialize communication with Computer Console
	
	__enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
	while(1) {
		//Nothing yet
		char LeString[60];
		sprintf(LeString, "1: %d RPM | 2: %d RPM \n\r", (int) getRPM(1), (int) getRPM(2));
		UARTIOSend(LeString);
		setRPM(1, SETPOINT);
		setRPM(2, SETPOINT2);
		__delay_cycles(100000);
	}
	return 0;
}
