/*
 * LineSensorDrive
 * this file does the following:
 * -initialize Line Sensor
 * -convert sensor reading to usable data
 * must have I2C_modual.c and .h in project
 * for resources used and guides refer to I2C_modual.h
 *
 */
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_modual.h"
#include "LineSensorDrive.h"


void LineSensorinit()
{
    increaseVCoreToLevel2();
       initClockTo16MHz();
       initGPIO();
       initI2C();
       unsigned char data = 0xff;
       unsigned char data1 = 0xFC;
       unsigned char data2 = 0X0;
       unsigned char data3 = 0x12;
       unsigned char data4 = 0x34;
       int num;
       int sen[30];
   /*
    * reset and configure line sensor
    */
       I2C_Master_WriteReg(SLAVE_ADDR, 0x7D, &data3, TYPE_0_LENGTH);
       I2C_Master_WriteReg(SLAVE_ADDR, 0X7D, &data4, TYPE_0_LENGTH);
       I2C_Master_WriteReg(SLAVE_ADDR, 0X0F, &data, TYPE_0_LENGTH);
       I2C_Master_WriteReg(SLAVE_ADDR, 0X0E, &data1, TYPE_0_LENGTH);
       I2C_Master_WriteReg(SLAVE_ADDR, 0X10, &data2, TYPE_0_LENGTH);

       //config finished
}

/*
 * LSRead
 * LS stands for Line Sensor
 */
char LSRead()
{
    char reading;
    unsigned char bitsCounted=0;
    int i;
    int accumulator;

    /*
     * read the raw data from sensor
     */
    I2C_Master_ReadReg(SLAVE_ADDR, 0x11, TYPE_0_LENGTH);
    CopyArray(ReceiveBuffer, SlaveType0, TYPE_0_LENGTH);

    //count bits
    for ( i = 0; i < 8; i++ )
    {
      if ( ((SlaveType0[0] >> i) & 0x01) == 1 )
      {
        bitsCounted++;
      }
    }

    //Find the vector value of each positive bit and sum
      for ( i = 7; i > 3; i-- ) //iterate negative side bits
      {
        if ( ((SlaveType0[0] >> i) & 0x01) == 1 )
        {
          accumulator += ((-32 * (i - 3)) + 1);
        }
      }
      for ( i = 0; i < 4; i++ ) //iterate positive side bits
      {
        if ( ((SlaveType0[0] >> i) & 0x01) == 1 )
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

      return lastBarPositionValue;

    }
