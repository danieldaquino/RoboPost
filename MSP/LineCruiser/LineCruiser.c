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
static float lastSensorError;
static double lastSharpness;

// Create variables that we can overwrite to in case of losing the line
static int internalSpeedSetpoint;
static float internalLastSensorPosition;


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
	static float accumDecay;
	if(lastRawSensorData == 0 || lastRawSensorData == 255) {
		// internalLastSensorPosition will be the latest valid one.
		accumDecay *= decayRate;
		// Decay until reaches 35% of speed
		internalSpeedSetpoint = speedSetpoint*(accumDecay + 0.35*(1-accumDecay));
	}
	else {
		accumDecay = 1;
		internalSpeedSetpoint = speedSetpoint;
		internalLastSensorPosition = lastSensorPosition;
	}
	
	// Get errors
	float sensorError = 0 - internalLastSensorPosition;
	float dSensorError = sensorError - lastSensorError;
	
	// Speed calculations
	int newSpeed;
	newSpeed = internalSpeedSetpoint*(1 - abs(dSensorError)*corneringDBrakeFactor - abs(sensorError)*corneringPBrakeFactor); // Slows down if line is moving too fast
	
	// Calculate Radius
	int newCurveRadius;
	newCurveRadius = -sharpestCurve/(cruiseKp*sensorError + cruiseKd*dSensorError);
	
	// Integrate Sharpness
	double newSharpness;
	newSharpness = cruiseKi*lastSharpness + 1/((double) newCurveRadius);
	// Add a saturation
	if(newSharpness > 1/((double) sharpestCurve) ) {
		newSharpness = 1/((double) sharpestCurve);
	}
	else if(newSharpness < -1/((double) sharpestCurve) ) {
		newSharpness = -1/((double) sharpestCurve);		
	}
	lastSharpness = newSharpness;
	
	// Get that into new curve radius
	newCurveRadius = 1/newSharpness;
		
	// Differential Drive
	diffDrive(newSpeed, newCurveRadius);
	
	// Record previous values
	lastSensorError = sensorError; // Record previous line position
}

char lineCruiserInit() {
	scheduleCallback(&controlCruise); // Schedule Control Cruise before the motor controller!
	//******************************
	diffDriverInit();	// Initialize Differential Drive. Should be after you scheduled control cruise. Should be before line Sensor	
	//******************************
	lineSensorInit();	// Initialize Line Sensor. Should be after diffDriverInit.
	
	// Default params
	speedSetpoint = 0;	// For safety
	sharpestCurve = 15;
	cruiseKd = 0.55;
	cruiseKp = 0.45;
	corneringDBrakeFactor = 0.95;
	corneringPBrakeFactor = 0.05;
	lastSharpness = 0;
	// 0.954^30Hz = 0.25/s, meaning speed will be divided by four every second.
	decayRate = 0.977;
	cruiseKi = 0.5;
	
	internalSpeedSetpoint = 0;
	internalLastSensorPosition = 0;
}