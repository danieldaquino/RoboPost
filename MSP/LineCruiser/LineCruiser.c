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

/*=======
Statics
========*/

/*=======
Static Function Prototypes
========*/
int speedSetpoint;

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
	float sensorReading;
	sensorReading = LSRead();
	diffDrive(speedSetpoint, (WHEEL_BASE/2)/sensorReading);
}

char lineCruiserInit(float speed) {
	diffDriverInit();	// Initialize Differential Drive	
	lineSensorInit();	// Initialize Line Sensor
	speedSetpoint = 0;	// Start at zero speed!
	scheduleCallback(&controlCruise);
}