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
}


void loop() {
	PhotonTCPServerLoop();
	// Fake gen the RobotGlobals
	RPMLS = 240 + 1*sin(millis()/100);
	RPML = 240 + 10*sin(millis()/100);
	RPMRS = 150 + 1*sin(millis()/200);
	RPMR = 150 + 10*sin(millis()/200);
	PWMLFWD = 0.5*sin(millis()/200) + 0.25;
	PWMLREV = 0.5*sin(millis()/300) + 0.25;
	PWMRFWD = 0.5*sin(millis()/200) + 0.5;
	PWMRREV = 0.4*sin(millis()/200) + 0.5;
	sensor = 0.4*sin(millis()/200) + 0.5;
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
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        return 0;
    }
    else {
        return -1;
    }
}
