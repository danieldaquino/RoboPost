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
#include "Photon_SPI_module/ucsiSpi.h"

// Includes just for diagnostics purposes
#include "LineCruiser/DiffDriver/DiffDriver.h"
#include "LineCruiser/DiffDriver/DualMotorController/DualMotorController.h"
#include "LineCruiser/LineSensorDriver/LineSensorDriver.h"

////////////////
#define ON_OFF  0x31
int main(void)
{
	//====== Initialization ==========
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	boostClockTo16MHz();	// Setup the CPU rate. MUST BE DONE BEFORE the other modules.
	ucsiB1SpiInit(SCLKDIV);
	//txData='A';
	unsigned char String[10]="ROBOPOST";
	P6OUT|=BIT5;
	P6DIR=BIT5;
	//unsigned int InfoBoard[15];
	uint32_t DataArray[10];
	uint32_t CommandArray[10];
	InfoBoardInit(DataArray,CommandArray);
	while(1) {
	    InfoBoardUpdate(DataArray,CommandArray);
	}
	return 0;
}
