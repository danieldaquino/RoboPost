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
	});
}

function TurnOffLED() {
	GetRequest("/ledOff").then(function(response) {
		console.log("Got Response:" + response);
	});
}
