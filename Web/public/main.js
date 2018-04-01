/*==============================

	Main.js
	
	RoboPost Web Interface
	
	Crafted by Daniel Walnut

===============================*/

/*======
Global Objects
=======*/

var PhotonKey = new Object();
var TheBotCanvas = new Object();
var UpdateMeasurementsInterval;

/*====================

	~~Load~~
	
	Main load function, after webpage loads

=====================*/
function Load() {
	// Setup the Canvas.
	document.getElementById("BotCanvas").width = window.innerWidth;
	document.getElementById("BotCanvas").height = window.innerHeight - 100;
	// Initialize Canvas controller, then render.
	TheBotCanvas = new VisualBot(document.getElementById("BotCanvas"), function() {
		TheBotCanvas.Render();
	});
	InitializeSettingsPanel();
	UpdateSettings();
	UpdateMeasurementsInterval = setInterval(UpdateMeasurements,500);
}

function ResizeCanvas() {
	document.getElementById("BotCanvas").width = window.innerWidth;
	document.getElementById("BotCanvas").height = window.innerHeight - 100;
	TheBotCanvas.Render();
}

function StartStop() {
	if(StartStop.RobotOn == undefined) {
		StartStop.RobotOn = false;	
	}
	if(StartStop.RobotOn == false) {
		StartStop.RobotOn = true;
		document.getElementById("StartStopButton").innerHTML = '<i class="fas fa-pause"></i>';
		document.getElementById("StartStopButton").classList.add("Activated");
		TurnOnLED();
	}
	else {
		StartStop.RobotOn = false;		
		document.getElementById("StartStopButton").innerHTML = '<i class="fas fa-play"></i>';
		document.getElementById("StartStopButton").classList.remove("Activated");
		TurnOffLED();
	}
}

function TurnOnLED() {
	GetRequest("/ledOn").then(function(response) {
		console.log("Got Response:" + response);
	}).catch(function(err) {
		console.log("Something went wrong while turning the LED on.");
		console.log(err);
	});
}

function TurnOffLED() {
	GetRequest("/ledOff").then(function(response) {
		console.log("Got Response:" + response);
	}).catch(function(err) {
		console.log("Something went wrong while turning the LED off.");
		console.log(err);
	});
}

function UpdateMeasurements() {
	GetJSON("/Measurements").then(function(response) {
		// Good! Let's update the Robot Object and then render.
		TheBotCanvas.Robot.SetPoints.RPM[0] = response.result.RPMLS.toFixed(2);
		TheBotCanvas.Robot.Measurements.RPM[0] = response.result.RPML.toFixed(2);
		TheBotCanvas.Robot.SetPoints.RPM[1] = response.result.RPMRS.toFixed(2);
		TheBotCanvas.Robot.Measurements.RPM[1] = response.result.RPMR.toFixed(2);
		TheBotCanvas.Robot.Measurements.PWM[0] = response.result.PWMLFWD.toFixed(2);
		TheBotCanvas.Robot.Measurements.PWM[1] = response.result.PWMRFWD.toFixed(2);
		TheBotCanvas.Render();
	}).catch(function(err) {
		console.log("Error in fetching Measurements!!");
		console.log(err);
	});
}
