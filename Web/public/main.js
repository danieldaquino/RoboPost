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
	// Now, let's try to make a call.
	GetRequest("/ledOn").then(function(response) {
		console.log("Got Response:" + response);
	});
}

