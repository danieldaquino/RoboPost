/*==============================

	CarRobot.js
	
	Mobile car robot virtual model Object
	
	Crafted by Daniel Walnut

===============================*/

/*==============================

	# Usage:
	
	## Creating new instance:
	
	var myRobot = new CarRobot();
	
	## Modifying values
	
	Just modify variables directly
	
	e.g.: 
	// Update left PWM to 50% duty cycle
	myRobot.Measurements.PWM[0] = 0.5;
	
===============================*/

function CarRobot() {
	var that = this;
	/*=======
	Robot State
	========*/
	that.Measurements = new Object();
	// PWM duty cycles
	that.Measurements.PWM = new Array();
	that.Measurements.PWM[0] = 0.3;
	that.Measurements.PWM[1] = 0.6;
	// PWM frequencies
	that.Measurements.F = new Array();
	that.Measurements.F[0] = "3K";
	that.Measurements.F[1] = "100 ";
	// Wheel RPMs
	that.Measurements.RPM = new Array();
	that.Measurements.RPM[0] = 250;
	that.Measurements.RPM[1] = 180;
	// General Robot Kinematics
	that.Measurements.CurveRadius = 500;
	that.Measurements.Speed = 0.6;
	
	/*=======
	Robot Setpoints
	========*/
	that.SetPoints = new Object();
	// Wheel RPMs
	that.SetPoints.RPM = new Array();
	that.SetPoints.RPM[0] = 270;
	that.SetPoints.RPM[1] = 150;
	// General Robot Kinematics
	that.SetPoints.CurveRadius = 400;
	that.SetPoints.Speed = 0.4;
	
	/*=======
	Robot Settings
	========*/
	that.Settings = new Object();
	that.Settings.RobotPlay = false;
	that.Settings.Motor = new Object();
	that.Settings.Motor.Kp = 0;
	that.Settings.Motor.Kd = 0;
	that.Settings.Cruise = new Object();
	that.Settings.Cruise.Kp = 0;
	that.Settings.Cruise.Kd = 0;
	that.Settings.Cruise.Sharpness = 0;
	
	/*=======
	Robot Parameters
	========*/
	that.MaxRPM = 300;
}
