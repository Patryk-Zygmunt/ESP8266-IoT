#include "pins_arduino.h"
#include "Alarm.h"
#include <LEAmDNS_Priv.h>
#include <LEAmDNS_lwIPdefs.h>
#include <LEAmDNS.h>
#include <ESP8266mDNS_Legacy.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServerSecureBearSSL.h>
#include <ESP8266WebServerSecureAxTLS.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include <dummy.h>
#include <WiFiUdp.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <CertStoreBearSSL.h>
#include <BearSSLHelpers.h>
#include <Arduino.h>;
#define HIGH 0x1
#define LOW  0x0

//void setup() {
//  Serial.begin(115200);
//  // put your setup code here, to run once:
//}
//
//void loop() {
//  GreetingProvider g;
//  std::string greeting = g.getGretting();
//  // Serial.print(greeting.c_str());
//  Serial.write(greeting.c_str());
//  delay(1000);
//  // put your main code here, to run repeatedly:
//}

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80
Alarm alarm;
static int sensorState = 0;

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
void handleSensorOn();
void handleSensorOff();
void handleLED();


void setup(void) {
	Serial.begin(115200);         // Start the Serial communication to send messages to the computer
	delay(10);
	Serial.println('\n');

	////laczenie z WiFi/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	wifiMulti.addAP("xD", "12345678");   // add Wi-Fi networks you want to connect to

	Serial.println("Connecting ...");
	int i = 0;
	while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		delay(250);
		Serial.print(++i); Serial.print(' ');
	}
	Serial.println('\n');
	Serial.print("Connected to ");
	Serial.println(WiFi.SSID());               // Tell us what network we're connected to
	Serial.print("IP address:\t");
	Serial.println(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer


////DNS -> http:// esp8266.local/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
		Serial.println("mDNS responder started");
	}
	else {
		Serial.println("Error setting up MDNS responder!");
	}


////HTTP server/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
	server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
	//server.on("/alarm", HTTP_GET, handleAlarm);
	server.on("/ALARM_ON", HTTP_GET, handleSensorOn);
	server.on("/ALARM_OFF", HTTP_GET, handleSensorOff);
	server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

	server.begin();                            // Actually start the server
	Serial.println("HTTP server started");
}

void loop(void) {
	server.handleClient(); // Listen for HTTP requests from clients
	alarm.setAlarm(sensorState);
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
	server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form><form action=\"/ALARM_ON\" method=\"POST\"><input type=\"submit\" value=\"Alarm ON\" /></form><form action=\"/ALARM_OFF\" method=\"POST\"><input type=\"submit\" value=\"Alarm OFF\" /></form><form>ALARM ???</form>");
}

void handleLED() {                          // If a POST request is made to URI /LED
	digitalWrite(D0, !digitalRead(D0));      // Change the state of the LED
	server.sendHeader("Location", "/");        // Add a header to respond with a new location for the browser to go to the home page again
	server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleSensorOn() {
	sensorState = HIGH;
}

void handleSensorOff() {
	sensorState = LOW;
}

void handleNotFound() {
	server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}