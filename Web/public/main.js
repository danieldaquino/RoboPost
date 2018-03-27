/*==============================

	Main.js
	
	RoboPost Web Interface
	
	Crafted by Daniel Walnut

===============================*/

/*======
Global Objects
=======*/

var PhotonKey = new Object();

/*====================

	~~Load~~
	
	Main load function, after webpage loads

=====================*/
function Load() {
	// Nothing yet.
	
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
