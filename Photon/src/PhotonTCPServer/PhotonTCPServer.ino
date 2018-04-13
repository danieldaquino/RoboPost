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
	~~streamMeasurements~~
	
	Sends a snapshot of current measurements as a MStream event.

	inputs: none
	outputs: none
	
	Globals used/affected: server
======*/
void streamMeasurements();

/*======
Functions
=======*/

void PhotonTCPServerInit() {
	// start listening for clients
	server.begin();
	incomingData = "";
	Particle.variable("incomingData", incomingData);
	Particle.publish("Setup", "TCP Server initialized.", 60, PUBLIC);
}

void PhotonTCPServerLoop() {
	/*=======
	Answer requests!
	========*/
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
	
	/*=======
	Send periodic events!
	========*/
	static int streamCounter;
	static int previousMillis;
	streamCounter += millis() - previousMillis;
	previousMillis = millis();
	if(streamCounter >= MSTREAM_REFRESH_PERIOD) {
		// If 0.1 s have passed since last reset...
		Particle.publish("TCPHandler", "Sending stream.", 60, PUBLIC);
		streamMeasurements();
		streamCounter = 0;
	}
}


void streamMeasurements() {
	// Allocate space
	StaticJsonBuffer<JSON_MAX_SIZE> outgoingJSONBuffer;
	// Create new JSON object for the response
	JsonObject& JSONResponse = outgoingJSONBuffer.createObject();
	
	// Prepare response
	JSONResponse["event"] = "MStream";
	JSONResponse["time"] = timeStamp;
	JsonObject& JSONResult = JSONResponse.createNestedObject("result");
	JSONResult["RPMLS"] = RPMLS;
	JSONResult["RPML"] = RPML;
	JSONResult["RPMRS"] = RPMRS;
	JSONResult["RPMR"] = RPMR;
	JSONResult["TA0CCR0_REG"] = TA0CCR0_REG;
	JSONResult["TA0CCR1_REG"] = TA0CCR1_REG;
	JSONResult["TA0CCR2_REG"] = TA0CCR2_REG;
	JSONResult["TA2CCR0_REG"] = TA2CCR0_REG;
	JSONResult["TA2CCR1_REG"] = TA2CCR1_REG;
	JSONResult["TA2CCR2_REG"] = TA2CCR2_REG;
	JSONResult["lastSensorPosition"] = lastSensorPosition;

	JSONResponse.printTo(server);
	// Finish it up by sending null character
	server.print('\0');
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
	if(strcmp(theCommand, "M") == 0) {
		// User wants measurements!
		JSONResponse["ID"] = LeJSON["ID"];
		JSONResponse["time"] = Time.now();
		JsonObject& JSONResult = JSONResponse.createNestedObject("result");
		JSONResult["RPMLS"] = RPMLS;
		JSONResult["RPML"] = RPML;
		JSONResult["RPMRS"] = RPMRS;
		JSONResult["RPMR"] = RPMR;
		JSONResult["TA0CCR0_REG"] = TA0CCR0_REG;
		JSONResult["TA0CCR1_REG"] = TA0CCR1_REG;
		JSONResult["TA0CCR2_REG"] = TA0CCR2_REG;
		JSONResult["TA2CCR0_REG"] = TA2CCR0_REG;
		JSONResult["TA2CCR1_REG"] = TA2CCR1_REG;
		JSONResult["TA2CCR2_REG"] = TA2CCR2_REG;
		JSONResult["lastSensorPosition"] = lastSensorPosition;

		JSONResponse.printTo(Serial);		
		JSONResponse.printTo(server);
		// Finish it up by sending null character
		server.print('\0');
	}
	else if(strcmp(theCommand, "SET") == 0) {
		// User wants to apply settings!
		JSONResponse["ID"] = LeJSON["ID"];
		JSONResponse["time"] = Time.now();
		
		sharpestCurve = LeJSON["variables"]["sharpestCurve"];
		cruiseKp = LeJSON["variables"]["cruiseKp"];
		cruiseKd = LeJSON["variables"]["cruiseKd"];
		corneringDBrakeFactor = LeJSON["variables"]["corneringDBrakeFactor"];
		corneringPBrakeFactor = LeJSON["variables"]["corneringPBrakeFactor"];
		motorKp = LeJSON["variables"]["motorKp"];
		motorKd = LeJSON["variables"]["motorKd"];
		Desired_Speed= LeJSON["variables"]["desiredSpeed"];
		
		JSONResponse["status"] = 0;
		
		JSONResponse.printTo(server);
		// Finish it up by sending null character
		server.print('\0');
	}
	else {
		Particle.publish("TCPHandler", "Error! Got a TCP request I don't understand.", 60, PUBLIC);
	}
}
