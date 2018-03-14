#ifndef LineSensorDrive_H_
#define LineSensorDrive_H_

/*
 * global var
 */
signed char lastBarPositionValue;

/*
 * function prototypes
 */

/*=========================
 * LineSensorinit
 *
 * this function is for initializing the line sensor array
 * intput:N/A
 * output:N/A
 *
 * globals affected:N/A
 *
 =========================*/
void LineSensorinit();

/*================================================
 * LSRead
 * LS stands for Line Sensor
 * this function will read the raw data from
 * sensor and process them to give usable numbers
 *
 * b7   b6   b5   b4   b3   b2   b1   b0
 * 128                                -126
 *
 * input: N/A
 * output: a char that reflect the position of the line read by sensor
 ======================================================*/
char LSRead();



#endif
