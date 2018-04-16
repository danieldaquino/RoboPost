#include "../ucsiSpi/ucsiSpi.h"
#include "Photon_SPI_Module.h"
#include <msp430.h>
#include "../Scheduler/Scheduler.h"
#include "DataErrorCheck/DataErrorCheck.h"

// Includes necessary to get the variables and change parameters
#include "../LineCruiser/DiffDriver/DualMotorController/DualMotorController.h"
#include "../LineCruiser/LineSensorDriver/LineSensorDriver.h"
#include "../LineCruiser/DiffDriver/DualMotorController/DualVelocityGauge/DualVelocityGauge.h"
#include "../LineCruiser/LineCruiser.h"
#include "../StartStop/StartStop.h"

/*=======
Static function prototypes
========*/

/*======
~~InfoBoardFill~~

Fills Info Board with measurements according to Info Board requirements

inputs: none
outputs: none

======*/
static void InfoBoardFill();

/*======
~~ReceiveInfoBoard~~

Fills parameters received at Infoboard

inputs: none
outputs: none

======*/
static void ReceiveInfoBoard();

/*=======
Functions
========*/

void InfoBoardUpdate() {
	InfoBoardFill();
	slaveSelect();
	__delay_cycles(50);
	
	spiTx_RXBytes(DataArray, CommandArray, NUM_PARAM);// transmit whats in dataArray and put received data in CommandArray

	slaveDeselect();
	__delay_cycles(200);  // wait for photon to process byte
	
	ReceiveInfoBoard();
}

static void InfoBoardFill() {
	// Fill it up!	
	int i;
	i=0;
	DataArray[i] = motorSetpoints[0];	// RPMLS
	i++;
	DataArray[i] = getRPM(1);			// RPML
	i++;
	DataArray[i] = motorSetpoints[1];	// RPMRS
	i++;
	DataArray[i] = getRPM(2);			// RPMR
	i++;
	DataArray[i] = TA0CCR0;				// TA0CCR0
	i++;
	DataArray[i] = TA0CCR1;				// TA0CCR1
	i++;
	DataArray[i] = TA2CCR2;				// TA0CCR2
	i++;
	DataArray[i] = TA2CCR0;				// TA2CCR0
	i++;
	DataArray[i] = TA2CCR1;				// TA2CCR1
	i++;
	DataArray[i] = TA2CCR2;				// TA2CCR2
	i++;
	DataArray[i] = lastSensorPosition;	// lastSensorPosition
	i++;
	DataArray[i] = Color;
	// Stamp checksum code
	stampMessage(DataArray, NUM_PARAM*4);
}

static void ReceiveInfoBoard() {
	// Perform checksum check
	if(checkDataError(CommandArray, NUM_PARAM*4)) {
		//There was error. Ignore.
		return;
	}
	else {
		int i;
		i = 0;
		robotPlay = CommandArray[i];
		i++;
		sharpestCurve = CommandArray[i];
		i++;
		cruiseKp = CommandArray[i];
		i++;
		cruiseKd = CommandArray[i];
		i++;
		corneringDBrakeFactor = CommandArray[i];
		i++;
		corneringPBrakeFactor = CommandArray[i];
		i++;
		motorKp = CommandArray[i];
		i++;
		motorKd = CommandArray[i];
		i++;
		Desired_Speed=CommandArray[i];
	}
}

void PhotonSPIModuleInit() {
	Desired_Speed = 0;
	dataErrorCheckInit();
	ucsiB1SpiInit();
	scheduleCallback(&InfoBoardUpdate);
}
