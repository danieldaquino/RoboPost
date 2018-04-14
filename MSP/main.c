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

/*=======
Function prototypes
========*/
/*========================

	~~ wifiSetCruiseSpeed ~~
	
	set the cruise speed from online command.
	
	inputs: none;
	outputs: none;
	Globals Affected: All globals commanded by lineCruiser. Check lineCruiser.h for more.

=========================*/
void wifiSetCruiseSpeed();

/*=======
Function definitions
========*/

int main(void)
{
	//====== Initialization ==========
	WDTCTL = WDTPW | WDTHOLD;				// (1) stop watchdog timer

	boostClockTo16MHz();					// (2) Setup the CPU rate. MUST BE DONE BEFORE the other modules.
	
	schedulerInit();						// (3) Setup scheduler somewhere before the line cruiser!!
	lineCruiserInit();						// (4) Initialize the line cruiser.
	setupStartStop();						// (6) Setup Start and Stop functionality
	PhotonSPIModuleInit();					// (7) Initialize SPI communications with Photon
	UARTIOInit(); 							// (8) Initialize communication with Computer Console
	
	// Schedule miscellaneous Callbacks
	scheduleCallback(&wifiSetCruiseSpeed);	// (9) Add Wifi Control of speed to the list of callbacks
	
	// Set initial values
	robotPlay = 0;
	
	// ********************************
	__enable_interrupt(); 	// Enable global interrupts. Everything must be configured before this.
	//==== Initialization Done. =======
	
	// Let's get this party started!
		
	schedulerRun();
	
	return 0;
}

void wifiSetCruiseSpeed() {
	lineCruise(Desired_Speed);
}