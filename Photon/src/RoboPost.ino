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
char robotPlay;


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
	
	// Setup misc
	robotPlay = 0;
	TA0CCR0_REG = 32;
	TA2CCR0_REG = 32;
}


void loop() {
	PhotonTCPServerLoop();
	// Fake gen the RobotGlobals
	if(robotPlay == 1) {
		RPMLS = 240 + 1*sin(millis()/100);
		RPML = 240 + 10*sin(millis()/100);
		RPMRS = 150 + 1*sin(millis()/200);
		RPMR = 150 + 10*sin(millis()/200);
		TA0CCR1_REG = (0.5*sin(millis()/200) + 0.25)*TA0CCR0_REG;
		TA0CCR2_REG = (0.5*sin(millis()/300) + 0.25)*TA0CCR0_REG;
		TA2CCR1_REG = (0.5*sin(millis()/200) + 0.5)*TA2CCR0_REG;
		TA2CCR2_REG = (0.4*sin(millis()/200) + 0.5)*TA2CCR0_REG;
		lastSensorPosition = 0.4*sin(millis()/200) + 0.5;
	}
	else {
		RPMLS = 150;
		RPML = 0;
		RPMRS = 150;
		RPMR = 0;
		TA0CCR1_REG = 0;
		TA0CCR2_REG = 0;
		TA2CCR1_REG = 0;
		TA2CCR2_REG = 0;
		lastSensorPosition = 0;		
	}
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
