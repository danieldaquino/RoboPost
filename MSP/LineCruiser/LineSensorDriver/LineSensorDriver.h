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
 * this function will read the raw data from sensor
 * 
 *
 * input: N/A
 * output: a char that reflects the position of the line read by sensor
 * globalsAffected : lastRawSensorData
 ======================================================*/
char LSRead();

/*================================================
 * scanLines
 *
 * Gets raw sensor data and separates individual track lines if there are multiple lines
 *
 * inputs: 
 *		(unsigned char) lineReading: the binary data to be processed
 *		(unsigned char *) lineReadingArray: Pointer to array where resulting individual lines will be written to
 											MUST BE OF SIZE 4
 *
 * char: return status: number of lines detected
 ======================================================*/
char scanLines(unsigned char lineReading, unsigned char * lineReadingArray);

/*================================================
 * LSCalcPosition
 * LS stands for Line Sensor
 * this function will calculate position from binary data of sensor
 * into give usable numbers
 *
 * b7   b6   b5   b4   b3   b2   b1   b0
 * -1                0                +1
 *
 * input: 
 *		(unsigned char) lineData: the binary data corresponding to a SINGLE line 
 * output: a float that reflects the position of the line
 * Globals affected : bitsCounted
 ======================================================*/
float LSCalcPosition(unsigned char lineData);

#endif
