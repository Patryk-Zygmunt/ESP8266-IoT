#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> // Include the WebServer library

#include "HTMLFactory.h"
#include "Event.h";
#include "Scheduler.h";

#define ROOT_HTML 0
#define ADD_EVENT_HTML 1
#define SET_HOUR_HTML 2

const char* ssid = "xD";
const char* password = "12345678";
MDNSResponder mdns;


int ledPin = 13;
int ledPin2 = 15;
int serverHour = 0;


ESP8266WebServer server(80); 

  
void handleRoot();              
void handleNotFound();
void handleLED();


HTMLFactory htmlFactory;
Scheduler scheduler;


void setup() {
    
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);

  Serial.begin(9600);

  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
    delay(500);
    Serial.print(".");    
  }

  Serial.println();

  Serial.println("WiFi Connected Success!");
  Serial.print("NodeMCU IP Adress :");
  Serial.println(WiFi.localIP());

 if( mdns.begin("esp8266-01", WiFi.localIP())){
  Serial.println("MDNS Responder success!");
 }


  // HTTP server
  server.on("/", HTTP_GET, handleRoot);       
  server.on("/addEventScreen", HTTP_GET, addEventScreen);
  server.on("/setHourScreen", HTTP_GET, setHourScreen);
       
  server.on("/addEvent", HTTP_POST, addEvent);   
  server.on("/setCurrentHour", HTTP_POST, setCurrentHour);    


  server.on("/printAllEvents", HTTP_GET, printAllEvents);    
   
  server.onNotFound(handleNotFound);           

  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");

  MDNS.addService("http", "tcp", 80);

}


void loop() {
  server.handleClient();
  
  int i = 0;
  for ( Event e : scheduler.eventsList ) {
      bool lightLed = false;
      lightLed = scheduler.nextStep(serverHour, i);
      if(lightLed){
        digitalWrite(e.getPin(), HIGH);  
      }
      else{
        digitalWrite(e.getPin(), LOW); 
      }
      i += 1;
  }
  
}


void handleRoot() {  
  server.send(200, "text/html", htmlFactory.getHTML(ROOT_HTML));
}

void addEventScreen() {
  server.send(200, "text/html", htmlFactory.getHTML(ADD_EVENT_HTML));
}

void setHourScreen() {
  server.send(200, "text/html", htmlFactory.getHTML(SET_HOUR_HTML));
}

void printAllEvents() {
  int i = 0;
  String message = "This is list of events: \n"; 
  String messagePin = ". Pin number: ";
  String messageHour = " Hour: ";
  for ( Event e : scheduler.eventsList ) {
      i += 1;
      message += i + messagePin + e.getPin() + messageHour + e.getHour() + "\n";
  }
  
  Serial.println(message);
  
  server.send(200, "text/plain", message);
 
}

void addEvent() { 

  String message1 = server.arg("pinNumber");
  int pin = atoi(message1.c_str()); 
  String message2 = server.arg("hour");
  int hour = atoi(message2.c_str()); 

  Serial.println(message1);
  Serial.println(message2);

  Event newEvent(pin, hour);

  scheduler.addEvent(newEvent);
  
  Serial.println("Event added");
  
  server.sendHeader("Location", "/");       
  server.send(303);                         
}

void setCurrentHour() { 

  String message1 = server.arg("currentHour");
  int cHour = atoi(message1.c_str()); 
  serverHour = cHour; 

  server.sendHeader("Location", "/");       
  server.send(303);                         
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}
