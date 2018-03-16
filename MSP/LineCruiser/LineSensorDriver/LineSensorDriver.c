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
}

float LSRead()
{
    char reading;
    unsigned char bitsCounted=0;
    int i;
    int accumulator;

    /*
     * read the raw data from sensor
     */
    uint8_t receiveBuffer[30];
    I2CRead(LINE_ADDRESS, 0x11, TYPE_0_LENGTH, receiveBuffer);
    
    lastRawSensorData = receiveBuffer[0];
    
    //count bits
    for ( i = 0; i < 8; i++ )
    {
      if ( ((receiveBuffer[0] >> i) & 0x01) == 1 )
      {
        bitsCounted++;
      }
    }

    //Find the vector value of each positive bit and sum
      for ( i = 7; i > 3; i-- ) //iterate negative side bits
      {
        if ( ((receiveBuffer[0] >> i) & 0x01) == 1 )
        {
          accumulator += ((-32 * (i - 3)) + 1);
        }
      }
      for ( i = 0; i < 4; i++ ) //iterate positive side bits
      {
        if ( ((receiveBuffer[0] >> i) & 0x01) == 1 )
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
