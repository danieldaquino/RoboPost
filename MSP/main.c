/*==========================================
 _____       _           _____          _   
|  __ \     | |         |  __ \        | |  
| |__) |___ | |__   ___ | |__) |__  ___| |_ 
|  _  // _ \| '_ \ / _ \|  ___/ _ \/ __| __|
| | \ \ (_) | |_) | (_) | |  | (_) \__ \ |_ 
|_|  \_\___/|_.__/ \___/|_|   \___/|___/\__|
                                            
by Daniel Walnut and Tim Yue

==========================================*/

#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CPUClock/CPUClock.h"
#include "Scheduler/Scheduler.h"
#include "LineCruiser/LineCruiser.h"
#include "UARTIO/UARTIO.h"
#include "StartStop/StartStop.h"

// Includes just for diagnostics purposes
#include "LineCruiser/DiffDriver/DiffDriver.h"
#include "LineCruiser/DiffDriver/DualMotorController/DualMotorController.h"
#include "LineCruiser/LineSensorDriver/LineSensorDriver.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	
	boostClockTo16MHz();	// Setup the CPU rate. MUST BE DONE BEFORE the other modules.
	
	schedulerInit();		// Setup scheduler before the line cruiser!!
	lineCruiserInit();		// Initialize the line cruiser.
	UARTIOInit(); 			// Initialize communication with Computer Console
	
	setupStartStop();
	
	// Let's get this party started!
	__enable_interrupt(); 	// Enable global interrupts. Everything must be configured before this.
	
	lineCruise(30); // Let's cruise at 30cm/s
	
	while(1) {
		//Nothing yet
		char LeString[150];
		int strSize;
		LSRead(); // CANNOT BE IN SCHEDULER BECAUSE IT NEEDS GIE TO WORK.
		//strSize = sprintf(LeString, "sensor: %d | 1: %d RPM | 2: %d RPM | S: %d cm/s | R: %d cm\n\r", (int) (lastSensorPosition*100), (int) getRPM(1), (int) getRPM(2), (int) getSpeed(), (int) getCurveRadius());
		//UARTIOSend(LeString, strSize);		
		__delay_cycles(1600000);
	}
	return 0;
}
