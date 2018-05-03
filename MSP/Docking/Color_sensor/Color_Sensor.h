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
#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

/*=====
Macros
======*/
#define CS_ADDR 0x29

/*=====
Globals
======*/
uint32_t Color;
uint32_t Command_Color;
unsigned long int RGBColor;

/*=====
Function prototypes
======*/

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

#endif
