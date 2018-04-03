/*===============================
	
	# PhotonTCPClient
                                            
	This module interfaces to Photon via TCP connection and acts as a client.
	
	For more information, read README.md
	
	Crafted by Daniel Walnut
	
===============================*/
var net = require('net');
var crypto = require('crypto');

/*======
Globals
=======*/
var PhotonClient;
var ConnectionStatus = false;
var RoboPostPackets = new Array();
var incomingBuffer = "";
var EventHandlers = new Array();

module.exports.ConnectToPhoton = function(PhotonIP) {
	return new Promise(function(resolve,reject) {
		// Create new Client
		PhotonClient = new net.Socket();
	
		//Try to connect
		PhotonClient.connect(23, PhotonIP, function() {
			// SUCCESS!! CONNECTED!
			resolve();
			console.log("Successfully connected to Photon.");
		
			ConnectionStatus = true;
		
			// INCOMING DATA
			PhotonClient.on('data', function(data) {
				for(var i = 0; i < data.length; i++) {
					if(data[i] == 0) {
						// Null character!! Chop it and handle this!
						// We need to put inside a "try" because we might be arriving at the middle of the message.
						// In this case we mus dispose of it.
						try {
							HandlePhotonData(JSON.parse(incomingBuffer));
						}
						catch(err) {
							console.log("Missed one message. Here is what I got:");
							console.log(incomingBuffer);
						}
						incomingBuffer = "";
					}
					else {
						// Not null character. Keep adding stuff...
						incomingBuffer += Buffer([data[i]]).toString('ascii');
					}
				}
			});
		});
	
		// On close
		PhotonClient.on('close', function() {
			console.log('TCP Connection closed');
			ConnectionStatus = false;
		});
		
		PhotonClient.on('error', function(err) {
			console.log('TCP Connection error');
			reject(err);
			ConnectionStatus = false;
		});	
	});
}

module.exports.SendToPhoton = function(command, variables) {
	// Check if connected
	if(ConnectionStatus){
		var PacketToSend = new RoboPostPacket(command, variables);
		RoboPostPackets[PacketToSend.message.ID] = PacketToSend;
		PhotonClient.write(JSON.stringify(PacketToSend.message) + '\0');
		return PacketToSend.Promise;
	}
	else {
		return Promise.reject("Cannot Reach Photon with TCP");
	}
}

module.exports.DisconnectPhoton = function() {
	PhotonClient.destroy();
}

module.exports.on = function(event, callback) {
	if(EventHandlers[event]) {
		// Event Handler exists! append callback.
		EventHandlers[event].push(callback);
	}
	else {
		// New event handler
		EventHandlers[event] = new Array();
		EventHandlers[event].push(callback);
	}
}

function HandlePhotonData(data) {
	// Process the data.
	if(RoboPostPackets[data.ID]) {
		// It is a response
		RoboPostPackets[data.ID].Resolve(data);
		RoboPostPackets[data.ID] = null;
		delete RoboPostPackets[data.ID];
	}
	else if(data.event) {
		// Is an event! Check if there is a handler for that.
		if(EventHandlers[data.event]) {
			// There is a handler! Let's get calling.
			for(var i = 0;i < EventHandlers[data.event].length;i++) {
				EventHandlers[data.event][i](data);
			}
		}
		else {
			// No handler. Keep quiet.
		}
	}
	else {
		console.log("Error: Received unsolicited data from Photon");
		console.log(data);
	}
}

function RoboPostPacket(command, variables) {
	var that = this;
	
	that.message = new Object();
	that.message.ID = crypto.randomBytes(5).toString('hex');
	that.message.command = command;
	that.message.variables = variables;
	
	that.Resolve = undefined;
	that.Reject = undefined;
	
	that.Promise = new Promise(function(resolve, reject) {
		// Export promise control functions
		that.Resolve = resolve;
		that.Reject = reject;
	});
	
	// Create timeout mechanism to prevent halts.
	setTimeout(function() {
		that.Reject("TCP Request Timed out.");
		RoboPostPackets[that.message.ID] = null;
		delete RoboPostPackets[that.message.ID];
	}, 3000);
}