#include <string>
#include <iostream>
#include <sstream>
#include <FS.h>
#include "ArduinoJson.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "init.h";
#include "utils.h";
#include "wifi.h";
#include "routes.h"
#include "static_file_handlers.h"
#include "server.h"
#include "ESPTimer.h"

ESPTimer timer;

void setup()
{
  pinMode(RESET_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  

  SPIFFS.begin();
  Serial.begin(115200);
  Serial.print("\n\n");
  delay(2000);
  handleReset();
  
  readStoredConfig();
  initializeWiFi();
  timer.initializeTimer();
  initializeWebServer();
  addRoutes();
  
  server.begin();
  delay(3000);
}

void loop()
{
  handleReset();
  logInfo();
  dnsServer.processNextRequest();
  server.handleClient();
}

void logInfo()
{
  static unsigned long lastStations = 0;
  int stations = WiFi.softAPgetStationNum();
  if (stations != lastStations)
  {
    lastStations = WiFi.softAPgetStationNum();
    Serial.printf("[  LOG   ] Stations connected = %d\n", stations);
  }
}