# PhotonTCPClient

This module interfaces to Photon via TCP connection and acts as a client.

## Format Specification:
	
Note: Everything in tags (<>) is variable
	
### General format to Photon:
	
	{
		"ID": <random_hash>,
		"command": <the_command>,
		"args": {
			<ALL_VARIABLES_HERE>
		}
	}
	
### General format from Photon:

#### Response type
	
	{
		"ID": <request_hash>,
		"time": <timestamp>,
		"result": {
			<ALL_VARIABLES_HERE>
		}
	}
	
#### Stream type

	{
		"event": <event>,
		"time": <timestamp>,
		"result": {
			<ALL_VARIABLES_HERE>
		}
	}


## Functions

### ConnectToPhoton
	
	Connects to Photon TCP Server
	
	inputs:
		localIP : Photon's local IP address
		
### SendPhoton
	
	Sends a packet to Photon through TCP connection.
	
	inputs:
		(string) command: the command
		(JSON) args: the arguments for specified command
		
	outputs: 
		(Promise): The Promise of the packet. Will resolve to the response JSON.
		
	Please check CommandReference.md for more info on commands and responses.

### HandlePhotonData
	
	Handles JSON data from photon.
	
	Photon responses should always be a response to our packets.

	
## RoboPostPacket
	
	Object type for a TCP packet between Photon and this server.
	
	Inputs:
		command : <command>
	
	Outputs: 
		RoboPostPacket Object
