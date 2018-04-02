/*
 * photonDriver
 * this file does the following:
 * -connect with photon
 * -receive from photon to usable data
 * must have I2C_modual.c and .h in project
 * for resources used and guides refer to I2C_modual.h
 *
 */
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_modual.h"
#include "photonDriver.h"

char data=0x01;
char slave=PHOTON_ADDR;
unsigned char photoninit()
{
    unsigned char success=1;
    unsigned char failed=0;
    increaseVCoreToLevel2();
           initClockTo16MHz();
           initGPIO();
           initI2C(slave);
    //I2C_Master_WriteReg(PHOTON_ADDR, 0xff,&data ,TYPE_0_LENGTH);
    I2C_Master_ReadReg(PHOTON_ADDR, 0, TYPE_0_LENGTH);
    CopyArray(ReceiveBuffer, SlaveType0, TYPE_0_LENGTH);
    if(SlaveType0==0x18)
    {
        return success;
    }
    else
    {
        return failed;
    }

}

char photon_read(char addr,char length)
{

    I2C_Master_ReadReg(PHOTON_ADDR, addr, length);
        CopyArray(ReceiveBuffer, SlaveType0, TYPE_0_LENGTH);
        return &SlaveType0;
}
