/*=================================
 * includes
 =================================*/
#include <msp430.h>
#include <stdint.h>
#include "I2CModule/I2CModule.h"
#include "Photon_SPI_module/Photon_SPI_Module.h"
#include "StartStop/StartStop.h"
#include "Color_Sensor.h"
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
    RGBColor = 0xFFFFFF;
}

char CSRead()
{
    uint8_t r=0;
    uint8_t g=0;
    uint8_t b=0;
    uint8_t receiveBuffer[2];
    I2CRead(CS_ADDR,COMMAND_BIT|RREG , 2, receiveBuffer);// read Red sensor reading
    r=receiveBuffer[0];
	I2CRead(CS_ADDR,COMMAND_BIT|GREG , 2, receiveBuffer);// read Blue sensor reading
	g=receiveBuffer[0];
    I2CRead(CS_ADDR,COMMAND_BIT|BREG , 2, receiveBuffer);// read Blue sensor reading
    b=receiveBuffer[0];
    if(r>60 && b<60 && g<60)
    {
        Color= 1;
    }
    else if(r<80 && b>80 && g>80)
    {
        Color= 2;
    }
    else
    {
        Color= 0;
    }
    RGBColor = (r << 16) | (g << 8) | b;
}



