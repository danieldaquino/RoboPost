#include "../ucsiSpi/ucsiSpi.h"
#include "Photon_SPI_Module.h"
#include <msp430.h>

// Includes necessary to get the variables
/*
#include "../LineCruiser/DiffDriver/DualMotorController/DualMotorController.h"
#include "../LineCruiser/LineSensorDriver/LineSensorDriver.h"
#include "../LineCruiser/DiffDriver/DualMotorController/VelocityGauge/VelocityGauge.h"
*/

void InfoBoardUpdate(uint32_t *DataArray,uint32_t *CommandArray)
{
	InfoBoardFill(DataArray);
	slaveSelect();
	__delay_cycles(50);
	
	spiTx_RXBytes(DataArray, CommandArray, NUM_PARAM);// transmit whats in dataArray and put received data in CommandArray

	// __delay_cycles(160);
	slaveDeselect();
	__delay_cycles(200);  // wait for photon to process byte
}

void InfoBoardFill(uint32_t *DataArray)
{
	// FAKE THE DATA
	int motorSetpoints[2];
	motorSetpoints[0] = 250;
	motorSetpoints[1] = 240;
	float lastSensorPosition;
	lastSensorPosition = 0.5;
	TA0CCR0 = 320;
	TA0CCR1 = 140;
	TA0CCR2 = 0;
	TA2CCR0 = 320;
	TA2CCR1 = 160;
	TA2CCR2 = 0;
	
	// Fill it up!	
	int i;
	i=0;
	DataArray[i] = motorSetpoints[0];	// RPMLS
	i++;
	DataArray[i] = 200;//(int) getRPM[0];	// RPML
	i++;
	DataArray[i] = motorSetpoints[1];	// RPMRS
	i++;
	DataArray[i] = 100;//(int) getRPM[1];	// RPMR
	i++;
	DataArray[i] = TA0CCR0;	// TA0CCR0
	i++;
	DataArray[i] = TA0CCR1;	// TA0CCR1
	i++;
	DataArray[i] = TA2CCR2;	// TA0CCR2
	i++;
	DataArray[i] = TA2CCR0;	// TA2CCR0
	i++;
	DataArray[i] = TA2CCR1;	// TA2CCR1
	i++;
	DataArray[i] = TA2CCR2;	// TA2CCR2
	i++;
	DataArray[i] = lastSensorPosition;	// lastSensorPosition
}
