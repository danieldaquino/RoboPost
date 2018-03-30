/*===============================

 _____       _           _____          _   
|  __ \     | |         |  __ \        | |  
| |__) |___ | |__   ___ | |__) |__  ___| |_ 
|  _  // _ \| '_ \ / _ \|  ___/ _ \/ __| __|
| | \ \ (_) | |_) | (_) | |  | (_) \__ \ |_ 
|_|  \_\___/|_.__/ \___/|_|   \___/|___/\__|
                                            
                                            
	Node.js Backend for RoboPost
	
	Crafted by Daniel Walnut
	
===============================*/

const express = require('express');
const app = express();
var request = require('request');
var fs = require('fs');

/*=======
Global Objects
========*/
var PhotonKeys = new Object();
var PhotonWeb = new Object();

function Start() {	
	// Show welcome message
	PrintBanner();
	// Get the keys
	PhotonKeys = JSON.parse(fs.readFileSync('keys.json', 'utf8'));
	console.log("Photon Key captured!");
	console.log("ID: " + PhotonKeys.ID);
	console.log("Token: " + PhotonKeys.Token);
	// Get IP then create the server
	GetLocalIP().then(function(response) {
		console.log("Photon's IP address: " + response);
		SetupServer();
	}).catch(function(err) {
		console.log("Error in fetching Photon's local IP address.")
	});
	// Start Server
}

/*====================

	~~SetupServer~~
	
	This function configures the server. 
	
	Make sure the photon keys are setup before calling requests!

=====================*/
function SetupServer() {
	app.get('/ledOn', function(req, res) {
		request.post({url: "https://api.particle.io/v1/devices/" + PhotonKeys.ID + "/led?access_token=" + PhotonKeys.Token, form: {arg:'on'}}, function(err,httpResponse,body) {
			if(!err) {
				res.send(body);
			}
			else {
				res.send(err);
			}
		});
	});
	
	app.get('/ledOff', function(req, res) {
		request.post({url: "https://api.particle.io/v1/devices/" + PhotonKeys.ID + "/led?access_token=" + PhotonKeys.Token, form: {arg:'off'}}, function(err,httpResponse,body) {
			if(!err) {
				res.send(body);
			}
			else {
				res.send(err);
			}
		});
	});
	
	// Serve public html files
	app.use(express.static('public'));
	
	app.listen(3000, function() {
		console.log('\n Now live at localhost:3000');
	});
}

/*====================

	~~GetJSON~~
	
	This function makes a get request to the given url, and gathers the json
	
	The function returns a promise, and the promise will resolve to the response json,
	or reject to the error.

=====================*/
function GetJSON(url) {
	return new Promise(function(resolve, reject) {
		request(url, function (error, response, body) {
			if(error != "" && error != null && error != undefined) {
				reject('error:', error); // Print the error if one occurred
			}
			else if(response.statusCode == 200) {
				resolve(JSON.parse(body));
			}
			else {
				reject("Request error. Got code " + response.statusCode);
			}
		});
	});
}

function GetLocalIP() {
	return new Promise(function(resolve, reject) {
		// Get the JSON
		GetJSON("https://api.particle.io/v1/devices/" + PhotonKeys.ID + "/localIP?access_token=" + PhotonKeys.Token).then(function(response) {
			// Success! Return
			resolve(response.result);		
		}).catch(function(err) {
			// Uh oh.
			reject(err);
		});		
	});
}

function PrintBanner() {
	console.log(fs.readFileSync('Welcome.txt', 'utf8'));
}

Start();