#include "ucsiSpi.h"
#include <msp430.h>
#include <stdint.h>

#define NUM_PARAM   11

unsigned char InfoBoardUpdate(int *DataArray,int *CommandArray);
void InfoBoardInit(int *DataArray,int *CommandArray);

unsigned char InfoBoardUpdate(int *DataArray,int *CommandArray)
{
	P6OUT&=~BIT5;       // enable SS
	__delay_cycles(50);
	spiTx_RXByte(DataArray,CommandArray,NUM_PARAM);// transmit whats in dataArray and put received data in CommandArray

	// __delay_cycles(160);
	P6OUT|=BIT5;    // disable SS
	__delay_cycles(200);  // wait for photon to process byte
}

void InfoBoardInit(int *DataArray,int *CommandArray)
{
    int i;
    for(i=0;i<2*10;i++)
        {
            *(DataArray+(i))=0x41+i;
            *(CommandArray+i)=0;
        }
}
