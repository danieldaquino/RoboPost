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
	// RevPWM duty cycles
	that.Measurements.RevPWM = new Array();
	that.Measurements.RevPWM[0] = 0.3;
	that.Measurements.RevPWM[1] = 0.6;
	// PWM frequencies
	that.Measurements.F = new Array();
	that.Measurements.F[0] = 100;
	that.Measurements.F[1] = 100;
	// Wheel RPMs
	that.Measurements.RPM = new Array();
	that.Measurements.RPM[0] = 250;
	that.Measurements.RPM[1] = 180;
	// General Robot Kinematics
	that.Measurements.CurveRadius = 500;
	that.Measurements.Speed = 0.6;
	// Color
	that.Measurements.Sensor = 0;
	that.Measurements.Color = 0;
	that.Measurements.RGBColor = 0;
	
	
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
	
	/*======
	Robot Targets
	=======*/
	that.Targets = new Object();
	that.Targets.CommandColor = 0;
	
	/*=======
	Robot Settings
	========*/
	that.Settings = new Object();
	that.Settings.DesiredSpeed = 0;
	that.Settings.Cruise = new Object();
	that.Settings.Cruise.Sharpness = 100;
	that.Settings.Cruise.Kp = 0;
	that.Settings.Cruise.Kd = 0;
	that.Settings.Cruise.Ki = 0;
	that.Settings.Cruise.DBrake = 0;
	that.Settings.Cruise.PBrake = 0;
	that.Settings.Cruise.DecayRate = 0;
	that.Settings.Motor = new Object();
	that.Settings.Motor.Kp = 0;
	that.Settings.Motor.Kd = 0;
	
	/*=======
	Robot Parameters
	========*/
	that.Parameters = new Object();
	that.Parameters.MaxRPM = 300;		// 300 rpm
	that.Parameters.WheelRadius = 3.5;	// 3.5cm
	that.Parameters.WheelBase = 18;		// 18cm
	
	/*=======
	Methods
	========*/
	that.SaveSettings = function() {
		localStorage.setItem("DesiredSpeed", that.Settings.DesiredSpeed);
		localStorage.setItem("CruiseSharpness", that.Settings.Cruise.Sharpness);
		localStorage.setItem("CruiseKp", that.Settings.Cruise.Kp);
		localStorage.setItem("CruiseKd", that.Settings.Cruise.Kd);
		localStorage.setItem("CruiseKi", that.Settings.Cruise.Ki);
		localStorage.setItem("DBrake", that.Settings.Cruise.DBrake);
		localStorage.setItem("PBrake", that.Settings.Cruise.PBrake);
		localStorage.setItem("DecayRate", that.Settings.Cruise.DecayRate);
		localStorage.setItem("MotorKp", that.Settings.Motor.Kp);
		localStorage.setItem("MotorKd", that.Settings.Motor.Kd);
	}
	
	that.RetrieveSettings = function() {
		that.Settings.DesiredSpeed = localStorage.getItem("DesiredSpeed") || that.Settings.DesiredSpeed;
		that.Settings.Cruise.Sharpness = localStorage.getItem("CruiseSharpness") || that.Settings.Cruise.Sharpness;
		that.Settings.Cruise.Kp = localStorage.getItem("CruiseKp") || that.Settings.Cruise.Kp;
		that.Settings.Cruise.Kd = localStorage.getItem("CruiseKd") || that.Settings.Cruise.Kd;
		that.Settings.Cruise.Ki = localStorage.getItem("CruiseKi") || that.Settings.Cruise.Ki;
		that.Settings.Cruise.DBrake = localStorage.getItem("DBrake") || that.Settings.Cruise.DBrake;
		that.Settings.Cruise.PBrake = localStorage.getItem("PBrake") || that.Settings.Cruise.PBrake;
		that.Settings.Cruise.DecayRate = localStorage.getItem("DecayRate") || that.Settings.Cruise.DecayRate;
		that.Settings.Motor.Kp = localStorage.getItem("MotorKp") || that.Settings.Motor.Kp;
		that.Settings.Motor.Kd = localStorage.getItem("MotorKd") || that.Settings.Motor.Kd;
	}
	
	that.UpdateMeasurements = function(RPMLS, RPML, RPMRS, RPMR, TA0CCR0_REG, TA0CCR1_REG, TA0CCR2_REG, TA2CCR0_REG, TA2CCR1_REG, TA2CCR2_REG, lastSensorPosition, Color) {
		// First update the RPMs, as they require least calculations.
		that.SetPoints.RPM[0] = RPMLS;
		that.Measurements.RPM[0] = RPML;
		that.SetPoints.RPM[1] = RPMRS;
		that.Measurements.RPM[1] = RPMR;
		
		// Then, update the sensor measurements
		that.Measurements.Sensor = lastSensorPosition;
		that.Measurements.Color = Color;
		
		// Then, calculate the duty cycles...
		that.Measurements.PWM[0] = TA0CCR1_REG/TA0CCR0_REG;
		that.Measurements.RevPWM[0] = TA0CCR2_REG/TA0CCR0_REG;
		that.Measurements.PWM[1] = TA2CCR1_REG/TA2CCR0_REG;
		that.Measurements.RevPWM[1] = TA2CCR2_REG/TA2CCR0_REG;
		
		// Then, calculate Frequencies...
		// Assume that Input Clock is 4MHz
		// f = 4MHz/TAxCCR0
		that.Measurements.F[0] = 4000000/TA0CCR0_REG;
		that.Measurements.F[1] = 4000000/TA2CCR0_REG;
		
		// Now the hardest part...
		// Calculate Actual Linear speed and actual curve radius based on RPMs
		// It takes diffDriver
		that.Measurements.CurveRadius = getCurveRadius(that.Measurements.RPM[0], that.Measurements.RPM[1]);
		that.Measurements.Speed = getSpeed(that.Measurements.RPM[0], that.Measurements.RPM[1]);
		// Calculate Setpoint Linear speed and setpoint curve radius based on RPM setpoints
		that.SetPoints.CurveRadius = getCurveRadius(that.SetPoints.RPM[0], that.SetPoints.RPM[1]);
		that.SetPoints.Speed = getSpeed(that.SetPoints.RPM[0], that.SetPoints.RPM[1]);		
	}
	
	/*=======
	Internal DiffDriver functions
	========*/
	var getWheelLinearSpeed = function(RPM) {
		// 2*pi/60 ==> 0.105. This is conversion factor from RPM to rad/s
		return RPM*(0.105)*that.Parameters.WheelRadius;
	}
	
	var getSpeed = function(RPML, RPMR) {
		var speed1 = getWheelLinearSpeed(RPML);
		var speed2 = getWheelLinearSpeed(RPMR);
		// The actual speed is the arithmetic mean of the linear speed of both wheels
		return (speed1 + speed2)/2;
	}
	
	var getCurveRadius = function(RPML, RPMR) {
		var speed1 = getWheelLinearSpeed(RPML);
		var speed2 = getWheelLinearSpeed(RPMR);
		// Derived somewhere.
		return (that.Parameters.WheelBase*(speed1+speed2))/(2*(speed1-speed2));
	}
}
