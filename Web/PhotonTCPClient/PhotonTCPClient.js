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
				incomingBuffer += Buffer(data).toString('ascii');
				try {
					HandlePhotonData(JSON.parse(incomingBuffer));
					incomingBuffer = "";
				} catch(err) {
					// Nothing
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

function HandlePhotonData(data) {
	// Process the data.
	if(RoboPostPackets[data.ID]) {
		console.log(data);
		RoboPostPackets[data.ID].Resolve(data);
		RoboPostPackets[data.ID] = null;
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
}