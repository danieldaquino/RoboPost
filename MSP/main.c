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
#include <stdint.h>

#include "CPUClock/CPUClock.h"
#include "Scheduler/Scheduler.h"
#include "LineCruiser/LineCruiser.h"
#include "UARTIO/UARTIO.h"
#include "StartStop/StartStop.h"
#include "Photon_SPI_Module/Photon_SPI_Module.h"

// Includes just for diagnostics purposes
#include "LineCruiser/DiffDriver/DiffDriver.h"
#include "LineCruiser/DiffDriver/DualMotorController/DualMotorController.h"
#include "LineCruiser/LineSensorDriver/LineSensorDriver.h"

int main(void)
{
	//====== Initialization ==========
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	boostClockTo16MHz();	// Setup the CPU rate. MUST BE DONE BEFORE the other modules.
	
	//schedulerInit();		// Setup scheduler before the line cruiser!!
	//lineCruiserInit();		// Initialize the line cruiser.
	UARTIOInit(); 			// Initialize communication with Computer Console
	//setupStartStop();		// Setup Start and Stop functionality
	ucsiB1SpiInit();
	I2CInit();
	ColorSensorInit();
	char coloor;
	

	__enable_interrupt(); 	// Enable global interrupts. Everything must be configured before this.
	
	//==== Initialization Done. =======
	
	// Let's begin with the robot stopped, for safety reasons
	//stopRobot();
	// Let's get this party started!
		
	while(1) {
	    LSRead();
	     coloor=CsRead();
	     //__delay_cycles(1000);
	     if(coloor==1)//red
	     {
	         while(1);
	     }
	     if(coloor==2)//blue
	             {
	                 while(1);
	             }

	}
	return 0;
}
