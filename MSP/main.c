#include <msp430.h> 
#include <stdio.h>

#include "DiffDriver/DualVelocityGauge/DualVelocityGauge.h"
#include "UARTIO.h"
#include "DiffDriver/DualMotorDriver/DualMotorDriver.h"


#define SETPOINT 250.0
/**
 * main func robopost.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	velocityGaugeInit(); //Initialize Gauge
	UARTIOInit(); // Initialize communication with Computer Console
	setupPWM(); //Start PWM with 50% duty cycle
	
	__enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
	while(1) {
		//Nothing yet
		char LeString[30];
		sprintf(LeString, "\fCurrent Speed: %d RPM\n\r", (int) getRPM(1));
		UARTIOSend(LeString);
		setDutyCycle(1, -(0.5 + ((SETPOINT - getRPM(1))/300)*0.5));
		__delay_cycles(100000);
	}
	return 0;
}
