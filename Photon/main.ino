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
Globals
=======*/
int led = D7;
IPAddress myIP;
String ipString;

// telnet defaults to port 23
TCPServer server = TCPServer(23);
TCPClient client;

void setup()
{
	//==== SETUP WEB LED ===
	// Configure pins
	pinMode(led, OUTPUT);
	
	// declare a Particle.function so that we can turn the LED on and off from the cloud.
	Particle.function("led", ledToggle);
	// This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
	
	// Make LED normally low.
	digitalWrite(led, LOW);
	//==== END SETUP WEB LED ===
	
	//==== SETUP LOCAL TCP SERVER ===
	
	// Make the local IP available in the cloud.
	updateLocalIP();
	Particle.variable("localIP", ipString);
	
	// start listening for clients
	server.begin();
	
}


void loop()
{
	if (client.connected()) {
		// echo all available bytes back to the client
		while (client.available()) {
			server.write(client.read());
		}
	} else {
		// if no client is yet connected, check for a new connection
		client = server.available();
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
