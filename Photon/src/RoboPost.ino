/*===============================

 _____       _           _____          _   
|  __ \     | |         |  __ \        | |  
| |__) |___ | |__   ___ | |__) |__  ___| |_ 
|  _  // _ \| '_ \ / _ \|  ___/ _ \/ __| __|
| | \ \ (_) | |_) | (_) | |  | (_) \__ \ |_ 
|_|  \_\___/|_.__/ \___/|_|   \___/|___/\__|
                                            
                                            
Photon Firmware

Crafted by Daniel Walnut and Tim Yue

===============================*/

/*======
Includes
=======*/
#include "PhotonTCPServer/PhotonTCPServer.h"
#include "SPI-WITH-MSP430/SPI-WITH-MSP430.h"
#include <math.h>
#include "RobotGlobals.h"

/*======
Macros
=======*/

/*======
Globals
=======*/
int led = D7;
IPAddress myIP;
String ipString;

// telnet defaults to port 23
TCPServer server = TCPServer(23);

void setup() {
	Particle.publish("Setup", "Starting...", 60, PUBLIC);
	//==== SETUP WEB LED ===
	// Configure pins
	pinMode(led, OUTPUT);
	
	// declare a Particle.function so that we can turn the LED on and off from the cloud.
	Particle.function("led", ledToggle);
	// This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
	
	// Make LED normally low.
	digitalWrite(led, LOW);
	Particle.publish("Setup", "Web LED Setup.", 60, PUBLIC);
	//==== END SETUP WEB LED ===
	
	//==== SETUP LOCAL TCP SERVER ===
	
	// Make the local IP available in the cloud.
	updateLocalIP();
	Particle.variable("localIP", ipString);
	Particle.publish("Setup", "Local IP available through the cloud.", 60, PUBLIC);
	
	PhotonTCPServerInit();
	//==== TCP SETUP COMPLETE ===
	
	//==== SETUP SPI ===
	SPIMSPSetup();
	//==== SPI IS SETUP ===
	
	// Setup misc
	robotPlay = 0;
	timeStamp = 0; // No time stamp yet...
	TA0CCR0_REG = 32;
	TA2CCR0_REG = 32;
	sharpestCurve = 100; // Tightest curve radius in cm
	cruiseKp = 0; // Proportional gain of the lineCruiser
	cruiseKd = 0; // Differential gain of the lineCruiser
	cruiseKi = 0; // Integral gain of the lineCruiser
	corneringDBrakeFactor = 0; // Number between 0 and 1 to tell how much to slow down in tightening curves. 0 means never slows down. 1 means full stop on tightest curve.
	corneringPBrakeFactor = 0; // Number between 0 and 1 to tell how much to slow down in a given curve. 0 means never slows down. 1 means full stop on tightest curve.
	decayRate = 0; // Number between 0 and 1 to tell how much to decay speed when loses a line
	motorKp = 0; // Proportional gain of the motors.
	motorKd = 0; // Differential gain of the motors.
	Desired_Speed = 35;
	commandColor = 0;
	desiredPathChosen = 0;
	RGBColor = 0xFFFFFF;
}


void loop() {
	PhotonTCPServerLoop();
	SPIMSPLoop();
	// Fake gen the RobotGlobals
}

void updateLocalIP() {
	myIP = WiFi.localIP();
	ipString = String(myIP[0])+"."+String(myIP[1])+"."+String(myIP[2])+"."+String(myIP[3]);
}

int ledToggle(String command) {
	/*
    This will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */
    if (command=="on") {
        digitalWrite(led,HIGH);
        robotPlay = 1;
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        robotPlay = 0;
        return 0;
    }
    else {
        return -1;
    }
}
