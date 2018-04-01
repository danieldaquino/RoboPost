/*===============================

	# PhotonTCPServer
	
	This Module acts as a TCP server for the Node.js Backend

================================*/
#include <Particle.h>
#include <string.h>
#include <ArduinoJson.h>
#include "PhotonTCPServer.h"

/*======
Macros
=======*/

/*======
Statics
=======*/
// telnet defaults to port 23
static TCPServer server = TCPServer(23);
static TCPClient client;
String incomingData;

/*======
Static function declarations
=======*/

/*======
	~~HandleIncomingData~~
	
	Handles incoming TCP data, as a String full of JSON

	inputs: (String) data: Stringified JSON
	outputs: none
	
	Globals used/affected: server
======*/
void HandleIncomingData(String data);

/*======
Functions
=======*/

void PhotonTCPServerInit() {
	// Initialize Serial port
	Serial.begin(9600);
	while (!Serial) continue;
	// start listening for clients
	server.begin();
	incomingData = "";
	Particle.variable("incomingData", incomingData);
	Particle.publish("Setup", "TCP Server initialized.", 60, PUBLIC);
}

void PhotonTCPServerLoop() {
	if (client.connected()) {
		// Concatenate all bytes into string to be processed.
		while (client.available()) {
			char nextByte;
			nextByte = client.read();
			incomingData.concat(String(nextByte));
			if(nextByte == '\0') {
				HandleIncomingData(incomingData);				
				incomingData = "";
			}
		}
	} else {
		// if no client is yet connected, check for a new connection
		client = server.available();
	}
}

void HandleIncomingData(String data) {
	// Create buffer to store data
	StaticJsonBuffer<JSON_MAX_SIZE> incomingJSONBuffer;
	char charBuf[JSON_MAX_SIZE];
	data.toCharArray(charBuf, data.length()+1);
	// Parse incoming JSON
	JsonObject& LeJSON = incomingJSONBuffer.parseObject(charBuf);
	// Create another buffer for the response
	StaticJsonBuffer<JSON_MAX_SIZE> outgoingJSONBuffer;
	// Create new JSON object for the response
	JsonObject& JSONResponse = outgoingJSONBuffer.createObject();
	
	const char * theCommand = LeJSON["command"];
	if(strcmp(theCommand,"M") == 0) {
		JSONResponse["ID"] = LeJSON["ID"];
		JSONResponse["time"] = Time.now();
		JsonObject& JSONResult = JSONResponse.createNestedObject("result");
		JSONResult["RPMLS"] = RPMLS;
		JSONResult["RPML"] = RPML;
		JSONResult["RPMRS"] = RPMRS;
		JSONResult["RPMR"] = RPMR;
		JSONResult["PWMLFWD"] = PWMLFWD;
		JSONResult["PWMLREV"] = PWMLREV;
		JSONResult["PWMRFWD"] = PWMRFWD;
		JSONResult["PWMRREV"] = PWMRREV;
		JSONResult["sensor"] = sensor;

		JSONResponse.printTo(Serial);		
		JSONResponse.printTo(server);
	}
	else {
		Particle.publish("TCPHandler", "Error! Got a TCP request I don't understand.", 60, PUBLIC);
	}
}
