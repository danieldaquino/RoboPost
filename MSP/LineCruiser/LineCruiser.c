/*===============================

	# LineCruiser
	
	This module allows you to make a robot follow a line
	
	For more information, resources and usage, please refer to LineCruiser.h
	
===============================*/

/*=======
Includes
========*/
#include "DiffDriver/DiffDriver.h"
#include "LineSensorDriver/LineSensorDriver.h"
#include "../Scheduler/Scheduler.h"
#include "LineCruiser.h"
#include <math.h>

/*=======
Statics
========*/
static int speedSetpoint;
static float lastLastSensorPosition;

/*=======
Static Function Prototypes
========*/

/*======
~~controlCruise~~

Routine function to update robot direction depending on sensor readings

To be called by the Scheduler

inputs: (none)
outputs: (none)
Globals affected: none
======*/
static void controlCruise(void);

/*=======
Function Definitions
========*/

char lineCruise(float speed) {
	speedSetpoint = speed;
	return 0;
}

static void controlCruise(void) {
	if(lastRawSensorData == 0 || lastRawSensorData == 255) {
		diffDrive(0, 32000); // If no line was detected, then stop the car.
		return;
	}
	float sensorPositionDifference;
	sensorPositionDifference = lastSensorPosition - lastLastSensorPosition;
	int newSpeed;
	newSpeed = speedSetpoint*(1 - abs(sensorPositionDifference)*CORNERING_D_SPEED_FACTOR - abs(lastSensorPosition)*CORNERING_P_SPEED_FACTOR); // Slows down if line is moving too fast
	int newCurveRadius;
	newCurveRadius = (TURN_NUMBNESS*WHEEL_BASE/2)/(CRUISE_KP*lastSensorPosition + CRUISE_KD*sensorPositionDifference); 								// Adjusts how much the car should turn, considering line position and how fast it is changing 
	diffDrive(newSpeed, newCurveRadius);
	lastLastSensorPosition = lastSensorPosition; // Record previous line position
}

char lineCruiserInit() {
	diffDriverInit();	// Initialize Differential Drive	
	lineSensorInit();	// Initialize Line Sensor
	speedSetpoint = 0;	// Start at zero speed!
	scheduleCallback(&controlCruise);
}