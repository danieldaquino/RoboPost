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

#include "PhotonRemote/PhotonRemote.c"
#include "PhotonRemote/PhotonRemote.h"

int led = D7;

void setup()
{

   // Configure pins
   pinMode(led, OUTPUT);

   // declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led", ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   // Make LED normally low.
   digitalWrite(led, LOW);
}


void loop()
{
   // Empty
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
