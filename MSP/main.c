#include <msp430.h> 
#include <stdio.h>

#include "VelocityGauge.h"
#include "UARTIO.h"
#include "PWMMotor.h"


#define SETPOINT 250.0
/**
 * main.c
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
		sprintf(LeString, "\fCurrent Speed: %d RPM\n\r", (int) getRPM());
		UARTIOSend(LeString);
		setDutyCycle(0.5 + ((SETPOINT - getRPM())/300)*0.5);
		__delay_cycles(100000);
	}
	return 0;
}
