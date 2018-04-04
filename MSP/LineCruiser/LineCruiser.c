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
static float lastSensorError;

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
	// Get errors
	float sensorError = 0 - lastSensorPosition;
	float dSensorError = sensorError - lastSensorError;
	
	// Speed calculations
	int newSpeed;
	newSpeed = speedSetpoint*(1 - abs(dSensorError)*corneringDBrakeFactor - abs(sensorError)*corneringPBrakeFactor); // Slows down if line is moving too fast
	
	// Calculate Radius
	int newCurveRadius;
	newCurveRadius = -sharpestCurve/(cruiseKp*sensorError + cruiseKd*dSensorError);
		
	// Differential Drive
	diffDrive(newSpeed, newCurveRadius);
	
	// Record previous values
	lastSensorError = sensorError; // Record previous line position
}

char lineCruiserInit() {
	diffDriverInit();	// Initialize Differential Drive	
	lineSensorInit();	// Initialize Line Sensor
	
	// Default params
	speedSetpoint = 0;	// For safety
	sharpestCurve = 15;
	cruiseKd = 0.55;
	cruiseKp = 0.45;
	corneringDBrakeFactor = 0.95;
	corneringPBrakeFactor = 0.05;
	
	scheduleCallback(&controlCruise);
}