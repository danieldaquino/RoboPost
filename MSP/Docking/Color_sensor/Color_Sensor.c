/*===============================

    Docking Module/Color_Sensor

    this C module is part of Docking function.
    It provides functions that allow you to communicate with color sensor which is needed for Docking.

    Written by Tim Yue and Daniel Walnut

    Resources used:

    1. port 3.0(SDA) & port 3.1（SCL)
    2. power pins 3.3V and GND
    3. UCSI(B0)

    Requirements:

    1. ArrayUtils module
    2. I2C_Module

===============================*/
/*=================================
 * includes
 =================================*/
#include <msp430.h>
#include <stdint.h>
#include "I2CModule/I2CModule.h"
#include "Photon_SPI_module/Photon_SPI_Module.h"
#include "StartStop/StartStop.h"
/*=================================
 * DEFINITIONS
 =================================*/
#define CS_ADDR 0x29
#define ID_reg  0x12
#define COMMAND_BIT 0X80
#define ATIME   0x01
#define Int50ms 0xEB
#define Gain    0x01
#define CONTROL 0x0F
#define ENABLE  0
#define PON     1
#define AEN     2
#define RREG    0x16
#define GREG    0x18
#define BREG    0x1A
#define CREG    0x14
#define RED     1
#define BLUE    2
/*==============================

    ~~ColorSensorInit~~

    Initializes the Color Sensor

    inputs: none
    outputs: none
    Globals Affected: none

==============================*/
void ColorSensorInit();
/*==============================

    ~~CsRead~~

    Get reading from color sensor and determine if it is blue or
    red or something else


    inputs: none
    outputs: 1 if red,2 if blue, 0 if something else
    Globals Affected: none

==============================*/
char CSRead();
void Docking();
void ColorSensorInit()
{
    uint8_t receiveBuffer[30];
    char Device_ID;
    uint8_t Data;
    //I2CWrite(CS_ADDR,COMMAND_BIT|ID_reg, TYPE_0_LENGTH);
    I2CRead(CS_ADDR,COMMAND_BIT|ID_reg , TYPE_0_LENGTH, receiveBuffer);
    Device_ID=receiveBuffer[0];
    if((Device_ID!=0x44)&&(Device_ID!=0x10))
    {
        while(1);
    }
    Data=Int50ms;
    I2CWrite(CS_ADDR,COMMAND_BIT|ATIME,&Data,TYPE_0_LENGTH);//set integration time to 50ms
    Data=Gain;
    I2CWrite(CS_ADDR,COMMAND_BIT|CONTROL,&Data,TYPE_0_LENGTH);//set Gain
    Data=PON;
    I2CWrite(CS_ADDR,COMMAND_BIT|ENABLE,&Data,TYPE_0_LENGTH);// turn on LED
    __delay_cycles(5);  //wait for led to fully turn on
    Data=PON|AEN;
        I2CWrite(CS_ADDR,COMMAND_BIT|ENABLE,&Data,TYPE_0_LENGTH);// enable color sensor
        scheduleInputCallback(&CSRead);
}
char CSRead()
{
    uint8_t r=0;
    uint8_t b=0;
    uint8_t receiveBuffer[2];
    uint8_t White=1;
    I2CRead(CS_ADDR,COMMAND_BIT|RREG , 2, receiveBuffer);// read Red sensor reading
    r=receiveBuffer[0];
    I2CRead(CS_ADDR,COMMAND_BIT|BREG , 2, receiveBuffer);// read Blue sensor reading
    b=receiveBuffer[0];
    if((r>100&&b<80)&&White==1)
    {
        Color= 1;
        White=0;
    }
    else if((r<80&&b>80)&&White==1)
    {
        Color= 2;
        White=0;
    }
    else
    {
        Color= 0;
        White=1;

    }


}



