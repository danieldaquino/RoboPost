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
