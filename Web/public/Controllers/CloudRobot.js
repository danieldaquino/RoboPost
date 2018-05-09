/*==============================

	CloudRobot.js
	
	The connection between this interface and the robot on the cloud.
	
	Requirements:
	
	1. CarRobot.js model
	2. socket.io
	3. HTTPRequest.js
	
	Crafted by Daniel Walnut

===============================*/

function CloudRobot(InputCarRobot, InputRobotDataCSV) {
	var that = this;
	
	// Save Car model
	that.CarRobot = InputCarRobot;
	// Save our CSV controller
	that.RobotDataCSV = InputRobotDataCSV;
	
	that.robotPlay = false;
	
	/*====
	WebSockets Handling
	=====*/	
	// Connect to Websockets server
	that.Socket = io();
	// Setup the measurement stream handler.
	that.Socket.on('MStream', function(data){
		that.UpdateMeasurements(data);
		if(that.robotPlay) {			
			that.AppendToCSV(data);
		}
	});
	
	that.Socket.on('StopSuccess', function(data){
		that.robotPlay = false;
	});
	
	/*====
	Cloud API Calls
	=====*/
	that.RobotPlay = function() {
		GetRequest("/robotPlay").then(function(response) {
			console.log("Turning robot on... Got Response:" + response);
			that.robotPlay = true;
		}).catch(function(err) {
			console.log("Something went wrong while turning the robot on.");
			console.log(err);
		});
	}

	that.RobotPause = function() {
		// FAST STOP
		that.Socket.emit('Stop');
		GetRequest("/robotPause").then(function(response) {
			console.log("Turning robot off... Got Response:" + response);
			that.robotPlay = false;
		}).catch(function(err) {
			console.log("Something went wrong while turning the robot off.");
			console.log(err);
		});
	}
	
	/*====
	Misc functions
	=====*/
	that.UpdateMeasurements = function(response) {
		that.CarRobot.UpdateMeasurements(
			response.result.RPMLS,
			response.result.RPML,
			response.result.RPMRS,
			response.result.RPMR,
			response.result.TA0CCR0_REG,
			response.result.TA0CCR1_REG,
			response.result.TA0CCR2_REG,
			response.result.TA2CCR0_REG,
			response.result.TA2CCR1_REG,
			response.result.TA2CCR2_REG,
			response.result.lastSensorPosition,
			response.result.color
		);
		TheBotCanvas.Render();
	}
	
	that.SendSettings = function() {
		var JSONToSend = new Object();
		JSONToSend.sharpestCurve = that.CarRobot.Settings.Cruise.Sharpness;
		JSONToSend.cruiseKp = that.CarRobot.Settings.Cruise.Kp;
		JSONToSend.cruiseKd = that.CarRobot.Settings.Cruise.Kd;
		JSONToSend.cruiseKi = that.CarRobot.Settings.Cruise.Ki;
		JSONToSend.corneringDBrakeFactor = that.CarRobot.Settings.Cruise.DBrake;
		JSONToSend.corneringPBrakeFactor = that.CarRobot.Settings.Cruise.PBrake;
		JSONToSend.decayRate = that.CarRobot.Settings.Cruise.DecayRate;
		JSONToSend.motorKp = that.CarRobot.Settings.Motor.Kp;
		JSONToSend.motorKd = that.CarRobot.Settings.Motor.Kd;
		JSONToSend.desiredSpeed = that.CarRobot.Settings.DesiredSpeed;
		JSONToSend.commandColor = that.CarRobot.Targets.CommandColor;
		JSONToSend.desiredPathChosen = that.CarRobot.Targets.PathChosen;

		PostRequest("/SET", JSON.stringify(JSONToSend)).then(function(response) {
			console.log("Success!");
			console.log(response);
		}).catch(function(err) {
			console.log("Something went wrong while turning the robot off.");
			console.log(err);
		});
	}
	
	that.AppendToCSV = function(response) {
		var CSVBuffer = "";
		that.RobotDataCSV.WriteRow([
			response.time,
			that.CarRobot.Measurements.Sensor,
			that.CarRobot.SetPoints.Speed,
			that.CarRobot.Measurements.Speed,
			that.CarRobot.SetPoints.CurveRadius,
			that.CarRobot.Measurements.CurveRadius,
			that.CarRobot.SetPoints.RPM[0],
			that.CarRobot.Measurements.RPM[0],
			that.CarRobot.SetPoints.RPM[1],
			that.CarRobot.Measurements.RPM[1],
			that.CarRobot.Measurements.F[0],
			that.CarRobot.Measurements.PWM[0],
			that.CarRobot.Measurements.F[1],
			that.CarRobot.Measurements.PWM[1],
			that.CarRobot.Measurements.RGBColor,
			0,
			that.CarRobot.Settings.DesiredSpeed,
			that.CarRobot.Settings.Cruise.Sharpness,
			that.CarRobot.Settings.Cruise.Kp,
			that.CarRobot.Settings.Cruise.Kd,
			that.CarRobot.Settings.Cruise.Ki,
			that.CarRobot.Settings.Cruise.DBrake,
			that.CarRobot.Settings.Cruise.PBrake,
			that.CarRobot.Settings.Cruise.DecayRate,
			that.CarRobot.Settings.Motor.Kp,
			that.CarRobot.Settings.Motor.Kd
		]);
	}
}