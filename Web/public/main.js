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
	// First, Load the keys
	GetJSON("keys.json").then(function(response) {
		PhotonKey = response;
	}).catch(function(err) {
		console.log("Error in loading key.json! make sure you have your key.json with proper token and photon ID. See ReadMe.");
	});
	// Now, let's try to make a call.
	GetRequest("/Hello").then(function(response) {
		console.log("Got Response:" + response);
	});
	/*
	PostRequest("https://api.particle.io/v1/devices/" + PhotonKey.ID + "/led?access_token=" + PhotonKey.Token).then(function(response) {
		console.log("Success! Response was" + response);
	}).catch(function(err) {
		console.log("Error!");
		console.log(err);
	});
	*/
}

