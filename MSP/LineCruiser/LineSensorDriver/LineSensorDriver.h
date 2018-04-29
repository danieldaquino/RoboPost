/*===============================

    Line Sensor Driver

    this C module is part of sensor interfacing.
    It provides functions that allow you to communicate with the line following sensor.

    Created by Tim Yue. Styled and Modified by Daniel Walnut

    Resources used:
    
    1. port 3.0(SDA) & port 3.1（SCL)
    2. power pins 5V and GND
    3. UCSI(B0)
    4. Scheduler Module
    
    Requirements:
    
    1. Array Utils module

===============================*/
#ifndef LINE_SENSOR_DRIVER_H_
#define LINE_SENSOR_DRIVER_H_

/*===================
 * Global variables
 ===================*/
char lastRawSensorData;				// the last raw sensor data
signed char lastBarPositionValue;	// Number from -128	to	+126
float lastSensorPosition;			// Number from -1	to	+1
unsigned char bitsCounted;

/*===================
 * sensor I2C address
 ===================*/
#define LINE_ADDRESS  0x3E

/*===================
 * Function prototypes
 ===================*/

/*=========================
 * lineSensorInit
 *
 * this function is for initializing the line sensor array
 * intput:N/A
 * output:N/A
 *
 * globals affected:N/A
 *
 =========================*/
void lineSensorInit();

/*================================================
 * LSRead
 * LS stands for Line Sensor
 * this function will read the raw data from
 * sensor and process them to give usable numbers
 *
 * b7   b6   b5   b4   b3   b2   b1   b0
 * -1                0                +1
 *
 * input: N/A
 * output: a char that reflects the position of the line read by sensor
 ======================================================*/
float LSRead();

#endif
