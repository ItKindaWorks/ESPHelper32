/*    
Copyright (c) 2018 ItKindaWorks All right reserved.
github.com/ItKindaWorks

This file is part of ESPHelper32

ESPHelper32 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ESPHelper32 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ESPHelper32.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	This is a simple MQTT relay/light controller program for the ESP8266.
	By sending a '1' or '0' to the relayTopic the relayPin can be toggled
	on or off. This program also posts a status update to the status topic
	which is the relayTopic plus "/status" (ex. if the relayTopic
	is "/home/light" then the statusTopic would be "home/light/status")
*/

#include "ESPHelper32.h"

#define TOPIC "/your/mqtt/topic"
#define STATUS TOPIC "/status"	//dont change this - this is for the status topic which is whatever your mqtt topic is plus /status (ex /home/light/status)

#define RELAY_PIN 3		//rx pin on esp
#define BLINK_PIN 1		//tx/led on esp-01


const char* relayTopic = TOPIC;
const char* statusTopic = STATUS;

const int relayPin = RELAY_PIN;
const int blinkPin = BLINK_PIN;		//tx pin on esp

netInfo homeNet = { .mqttHost = "YOUR MQTT-IP",     //can be blank if not using MQTT
					.mqttUser = "YOUR MQTT USERNAME",   //can be blank
					.mqttPass = "YOUR MQTT PASSWORD",   //can be blank
					.mqttPort = 1883,         //default port for MQTT is 1883 - only chance if needed.
					.ssid = "YOUR SSID", 
					.pass = "YOUR NETWORK PASS",
					.otaPassword = "YOUR OTA PASS",
					.hostname = "NEW-ESP8266"}; 

ESPHelper32 myESP(&homeNet);

void setup() {
	//setup ota
	myESP.OTA_enable();
	myESP.OTA_setPassword(homeNet.otaPassword);
	myESP.OTA_setHostnameWithVersion(homeNet.hostname);
	

	//setup the rest of ESPHelper
	myESP.enableHeartbeat(blinkPin);	//comment out to disable the heartbeat
	myESP.addSubscription(relayTopic);	//add the relay topic to the subscription list
	myESP.setMQTTCallback(callback);
	myESP.begin();
	

	pinMode(relayPin, OUTPUT);
    delay(100);
}


void loop(){
	//loop ESPHelper and wait for commands from mqtt
	myESP.loop();
	yield();
}


//mqtt callback
void callback(char* topic, byte* payload, unsigned int length) {
	String topicStr = topic;

	//if the payload from mqtt was 1, turn the relay on and update the status topic with 1
	if(payload[0] == '1'){
		digitalWrite(relayPin, HIGH);
		myESP.publish(statusTopic, "1",true);
	}

	//else turn the relay off and update the status topic with 0
	else if (payload[0] == '0'){
		digitalWrite(relayPin, LOW);
		myESP.publish(statusTopic, "0", true);
	}

}
