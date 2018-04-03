#include "ucsiSpi.h"
#include <msp430.h>
#include <stdint.h>

void InfoBoardUpdate(int *DataArray,int *CommandArray)
{
	slaveSelect();
	__delay_cycles(50);
	
	spiTx_RXBytes(DataArray, CommandArray, NUM_PARAM);// transmit whats in dataArray and put received data in CommandArray

	// __delay_cycles(160);
	slaveDeselect();
	__delay_cycles(200);  // wait for photon to process byte
}

void InfoBoardInit(int *DataArray,int *CommandArray)
{
    int i;
    for(i=0;i<2*10;i++)
        {
            *(DataArray+(i))=0x41+i;	// Fill in with 0x41: test data.
            *(CommandArray+i)=0;
        }
}
