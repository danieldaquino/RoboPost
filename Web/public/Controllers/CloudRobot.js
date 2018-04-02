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
	
	/*====
	WebSockets Handling
	=====*/	
	// Connect to Websockets server
	that.Socket = io();
	// Setup the measurement stream handler.
	that.Socket.on('MStream', function(data){
		that.UpdateMeasurements(data);
		that.AppendToCSV(data);
	});
	
	/*====
	Cloud API Calls
	=====*/
	that.RobotPlay = function() {
		GetRequest("/robotPlay").then(function(response) {
			console.log("Turning robot on... Got Response:" + response);
		}).catch(function(err) {
			console.log("Something went wrong while turning the robot on.");
			console.log(err);
		});
	}

	that.RobotPause = function() {
		GetRequest("/robotPause").then(function(response) {
			console.log("Turning robot off... Got Response:" + response);
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
			response.result.lastSensorPosition			
		);
		TheBotCanvas.Render();
	}
	
	that.AppendToCSV = function(response) {
		var CSVBuffer = "";
		that.RobotDataCSV.WriteRow([
			response.time,
			that.CarRobot.SetPoints.RPM[0],
			that.CarRobot.Measurements.RPM[0],
			that.CarRobot.SetPoints.RPM[1],
			that.CarRobot.Measurements.RPM[1],
			that.CarRobot.Measurements.PWM[0],
			that.CarRobot.Measurements.PWM[1]
		]);
	}
}