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
#include "../ArrayUtils/ArrayUtils.h"
#include <math.h>



/*=======
Statics
========*/
static int speedSetpoint;
static float lastSensorError;
static double lastSharpness;

// Recovery related variables
static unsigned char previousArrayOfLines[4];
static float lastStableLinePositions[4];
static char previousNumberOfLines;
static char previousChosenPath;
static char forkRecoveryMode;

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
		// ZERO LINE RECOVERY!
		// internalLastSensorPosition will be the latest valid one.
		accumDecay *= decayRate;
		// Decay until reaches 15cm/s of speed
		internalSpeedSetpoint = speedSetpoint*accumDecay + 15*(1-accumDecay);
	}
	else {
		// There is at least one line...
		unsigned char arrayOfLines[4];
		char numberOfLines;
		// Separate lines
		numberOfLines = scanLines(lastRawSensorData, arrayOfLines);
		
		// Check if we just lost a line in a fork.
		if((numberOfLines == 1 && previousNumberOfLines == 2)) {
			// We might have lost a line.
			// BEGIN FORK LINE RECOVERY!
			char i;
			// For each of the previous lines, calculate last stable line positions
			for(i=3;i > 1;i--) {
				lastStableLinePositions[i] = LSCalcPosition(previousArrayOfLines[i]);
			}
			float distanceBetweenEachOther;
			distanceBetweenEachOther = lastStableLinePositions[3] - lastStableLinePositions[2];
			// Absolute
			if(distanceBetweenEachOther < 0) {
				distanceBetweenEachOther = -distanceBetweenEachOther;
			}
			// Only start recovery mode if the previous lines are relatively far apart and NOT CONVERGING!
			if(distanceBetweenEachOther > 1) {
				forkRecoveryMode = 1;
			}
			else {
				forkRecoveryMode = 0;
			}
		}
		
		// Handle fork recovery mode (if we are still in it)
		if((forkRecoveryMode == 1) && numberOfLines == 1) {
			// We are still in fork recovery mode !!
			float currentLineCandidatePosition;
			// Calculate the current and only line, to see if it is good to follow.
			currentLineCandidatePosition = LSCalcPosition(arrayOfLines[3]);
			// Calculate distance from right line
			float distanceFromR;
			distanceFromR = currentLineCandidatePosition - lastStableLinePositions[3];
			// Get the absolute
			if(distanceFromR < 0) {
				distanceFromR = -distanceFromR;
			}
			// Calculate distance from left line
			float distanceFromL;
			distanceFromL = currentLineCandidatePosition - lastStableLinePositions[2];
			// Get the absolute
			if(distanceFromL < 0) {
				distanceFromL = -distanceFromL;
			}
			// Check if the candidate is closest to the line
			if(previousChosenPath == 1) {
				// We wanted to go RIGHT
				if(distanceFromR > distanceFromL) {
					// We are probably seeing the LEFT line.
					// Continue on the fork recovery mode.
					// internalLastSensorPosition will be the latest valid one.
					accumDecay *= decayRate;
					// Decay until reaches 15cm/s of speed
					internalSpeedSetpoint = speedSetpoint*accumDecay + 15*(1-accumDecay);
				}
				else {
					// We are seeing the correct line! Get out of fork recovery mode.
					forkRecoveryMode = 0;
				}
			}
			else {
				// We wanted to go LEFT
				if(distanceFromR < distanceFromL) {
					// We are probably seeing the RIGHT line.
					// Continue on the fork recovery mode.
					// internalLastSensorPosition will be the latest valid one.
					accumDecay *= decayRate;
					// Decay until reaches 15cm/s of speed
					internalSpeedSetpoint = speedSetpoint*accumDecay + 15*(1-accumDecay);
				}
				else {
					// We are seeing the correct line! Get out of fork recovery mode.
					forkRecoveryMode = 0;
				}
			}
		}
		
		// If fork recovery mode is off, go back to normal...
		if(forkRecoveryMode == 0) {		
			// Choose a path
			if(pathChosen == 1) {
				// We want to go RIGHT
				internalLastSensorPosition = LSCalcPosition(arrayOfLines[3]);
			}
			else {
				// We want to go LEFT
				internalLastSensorPosition = LSCalcPosition(arrayOfLines[4 - numberOfLines]);			
			}
		
			// No recovery. Just normal operation
			accumDecay = 1;
			internalSpeedSetpoint = speedSetpoint;
			previousNumberOfLines = numberOfLines;
			CopyArray(arrayOfLines, previousArrayOfLines, 4);
			forkRecoveryMode = 0;
			previousChosenPath = pathChosen;
		}
	}
	
	// Get errors
	float sensorError = 0 - internalLastSensorPosition;
	float dSensorError = sensorError - lastSensorError;
	
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
	
	internalSpeedSetpoint = 0;
	internalLastSensorPosition = 0;
	
	forkRecoveryMode = 0;
}
