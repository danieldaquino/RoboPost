/*==============================

	Server.js
	
	Server for RoboPost Web Interface.
	
	This code serves the webpages, and acts as a proxy to the Particle Cloud.
	
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

function Start() {	
	// Show welcome message
	console.log("=====================");
	console.log("Welcome to RoboPost!");
	console.log("=====================");
	// Get the keys
	PhotonKeys = JSON.parse(fs.readFileSync('keys.json', 'utf8'));
	console.log("Photon Key captured!");
	console.log("ID: " + PhotonKeys.ID);
	console.log("Token: " + PhotonKeys.Token);
	// Start Server
	SetupServer();
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
			debugger;
			if(error != "") {
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

Start();