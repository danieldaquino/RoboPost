/*===============================

    Line Sensor Driver

   this file does the following:
   
   1. Initialize Line Sensor
   2. Convert sensor reading to usable data

    for resources used and guides refer to I2CModule.h

===============================*/
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "../../I2CModule/I2CModule.h"
#include "LineSensorDriver.h"
#include "../../ArrayUtils/ArrayUtils.h"
#include "../../Scheduler/Scheduler.h"

/*=====
Static Function Prototypes
=====*/
/*================================================
 * findPositiveEdges
 * Finds positive edges, and displays at a bit higher than the first "1" value
 * 
 *
 * input: (char) lineReading: raw data
 * output: a char that shows the edges. edges will show as "1" at the bit to the left of the edge
 ======================================================*/
static char findPositiveEdges(char lineReading);

/*================================================
 * findRightMostEdgeMask
 * Finds a mask for the rightmost line
 * 
 *
 * input: (char) linePositiveEdges: edges
 * output: a char that shows the mask
 ======================================================*/
static char findRightmostEdgeMask(char linePositiveEdges);

/*================================================
 * findRightmostLine
 * Finds the rightmost line
 * 
 *
 * input: (char) lineReading: raw dara
 * output: a char that shows rightmost line
 ======================================================*/
static char findRightmostLine(char lineReading);

/*======
Functions
=======*/

void lineSensorInit()
{
	I2CInit();
	unsigned char data = 0xFF;
	unsigned char data1 = 0xFC;
	unsigned char data2 = 0x0;
	unsigned char data3 = 0x12;
	unsigned char data4 = 0x34;
	
	
   /*
    * reset and configure line sensor
    */
	I2CWrite(LINE_ADDRESS, 0x7D, &data3, TYPE_0_LENGTH);
	I2CWrite(LINE_ADDRESS, 0x7D, &data4, TYPE_0_LENGTH);
	I2CWrite(LINE_ADDRESS, 0x0F, &data, TYPE_0_LENGTH);
	I2CWrite(LINE_ADDRESS, 0x0E, &data1, TYPE_0_LENGTH);
	I2CWrite(LINE_ADDRESS, 0x10, &data2, TYPE_0_LENGTH);
	// config finished
	
	scheduleInputCallback(&LSRead);
}

char LSRead()
{
    /*
     * read the raw data from sensor
     */
    uint8_t receiveBuffer[30];
    I2CRead(LINE_ADDRESS, 0x11, TYPE_0_LENGTH, receiveBuffer);
    
    lastRawSensorData = receiveBuffer[0];
    
	return lastRawSensorData;
}

char scanLines(unsigned char lineReading, unsigned char * lineReadingArray)
{
	char numberOfLines;
	// Default 1, otherwise might produce errors
	numberOfLines = 1;
	
	int i;
	for(i=3;i > 0;i--) {
		lineReadingArray[i] = findRightmostLine(lineReading);
		if(lineReadingArray[i] == 0) {
			numberOfLines = 3 - i;
			break;
		}
		lineReading &= ~lineReadingArray[i];
	}
	return numberOfLines;
}

static char findRightmostLine(char lineReading)
{
  return lineReading&findRightmostEdgeMask(findPositiveEdges(lineReading));
}

static char findRightmostEdgeMask(char linePositiveEdges)
{
  char indexingBit = 0x01;
  char count = 0;
  while(!(indexingBit & linePositiveEdges)) {
    indexingBit = indexingBit << 1;
    count++;
    if(count >= 8) {
      break;
    }
  }
  return (indexingBit-1);
}

static char findPositiveEdges(char lineReading)
{
  return (lineReading<<1)&~(lineReading);
}

float LSCalcPosition(unsigned char lineData)
{
    char reading;
    int i;
    int accumulator;
	signed char lastBarPositionValue;	// Number from -128	to	+126
	float lastSensorPosition;			// Number from -1	to	+1

    bitsCounted=0;
    accumulator = 0;
    
    //count bits
    for ( i = 0; i < 8; i++ )
    {
      if ( ((lineData >> i) & 0x01) == 1 )
      {
        bitsCounted++;
      }
    }

    //Find the vector value of each positive bit and sum
      for ( i = 7; i > 3; i-- ) //iterate negative side bits
      {
        if ( ((lineData >> i) & 0x01) == 1 )
        {
          accumulator += ((-32 * (i - 3)) + 1);
        }
      }
      for ( i = 0; i < 4; i++ ) //iterate positive side bits
      {
        if ( ((lineData >> i) & 0x01) == 1 )
        {
          accumulator += ((32 * (4 - i)) - 1);
        }
      }

      if ( bitsCounted > 0 )
      {
        lastBarPositionValue = accumulator / bitsCounted;
      }
      else
      {
        lastBarPositionValue = 0;
      }
      
      // Get rid of rollover on extreme right.
      lastBarPositionValue--;
      
      lastSensorPosition = ((float) lastBarPositionValue)/128;

      return lastSensorPosition;
}
