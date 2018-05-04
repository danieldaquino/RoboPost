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
#include "StartStop/StartStop.h"
#include <math.h>



/*=======
Statics
========*/
static int speedSetpoint;
static float lastSensorError;
static double lastSharpness;
static float iSensorError;

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

char lineCruise(float speed, char desiredPath) {
	speedSetpoint = speed;
	pathChosen = desiredPath;
	return 0;
}

static void controlCruise(void) {
	static float accumDecay;
	// Check if we are off the line
	if(lastRawSensorData == 0 || lastRawSensorData == 255) {
		// internalLastSensorPosition will be the latest valid one.
		accumDecay *= decayRate;
		// Decay until reaches 15cm/s of speed
		internalSpeedSetpoint = speedSetpoint*accumDecay + 15*(1-accumDecay);
	}
	else {
		accumDecay = 1;
		internalSpeedSetpoint = speedSetpoint;
		unsigned char arrayOfLines[4];
		char numberOfLines;
		// Separate lines
		numberOfLines = scanLines(lastRawSensorData, arrayOfLines);
		// Choose a path
		if(pathChosen == 1) {
			// We want to go RIGHT
			internalLastSensorPosition = LSCalcPosition(arrayOfLines[3]);
		}
		else {
			// We want to go LEFT
			internalLastSensorPosition = LSCalcPosition(arrayOfLines[4 - numberOfLines]);			
		}
		
	}
	
	// Get errors
	float sensorError = 0 - internalLastSensorPosition;
	float dSensorError = sensorError - lastSensorError;
	iSensorError += sensorError;
	if(iSensorError > 1) {
		iSensorError = 1;
	}
	else if(iSensorError < -1) {
		iSensorError = -1;
	}
	
	// Speed calculations
	float newSpeed;
	float absSensorError;
	float absDSensorError;
	if(sensorError < 0) {
		absSensorError = -sensorError;
	}
	else {
		absSensorError = sensorError;
	}
	if(dSensorError < 0) {
		absDSensorError = -dSensorError;
	}
	else {
		absDSensorError = dSensorError;		
	}
	newSpeed = ((float) internalSpeedSetpoint)*(1 - absDSensorError*corneringDBrakeFactor - absSensorError*corneringPBrakeFactor); // Slows down if line is moving too fast
	
	// Calculate Radius
	float newCurveRadius;
	newCurveRadius = -sharpestCurve/(cruiseKp*sensorError + cruiseKd*dSensorError + cruiseKi*iSensorError);
			
	// Differential Drive
	diffDrive(newSpeed, newCurveRadius);
	
	// Record previous values
	lastSensorError = sensorError; // Record previous line position
}

char lineCruiserInit() {
	scheduleCallback(&controlCruise); // Schedule Control Cruise before the motor controller!
	//******************************
	diffDriverInit();	// Initialize Differential Drive. Should be after you scheduled control cruise. Should be before line Sensor	
	//****************************
	lineSensorInit();	// Initialize Line Sensor. Should be after diffDriverInit.
	ColorSensorInit();  // Initialize Color Sensor
	scheduleCallback(&Docking); // Schedule Control Cruise before the motor controller!
	
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
	
	pathChosen = 0;
	
	iSensorError = 0;
	
	internalSpeedSetpoint = 0;
	internalLastSensorPosition = 0;
}
