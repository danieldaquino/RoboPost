#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "VelocityGauge.h"
#include "UARTIO.h"
#include "PWMMotor.h"
#include "I2C_modual.h"

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

   LineSensorinit();
   int sen[10];
   char status_UART;
   char reading;

    __enable_interrupt(); // Enable global interrupts. Everything must be configured before this.
    while (1)
    {
        reading=LSRead();
        sprintf(sen,"\n\rreading:%d\n\r",reading);
        UARTIOSend(&sen);


    }
    return 0;
}
