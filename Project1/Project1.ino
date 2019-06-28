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
#include "time_service.h"
#include "scheduler_service.h"

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

  // std::chrono::system_clock::time_point tp = timePointFromString("2019-02-10 12:13", "%Y-%m-%d %H:%M");
  // Serial.println(timePointToString(tp,"%Y-%m-%d %H:%M").c_str());

  // std::chrono::system_clock::time_point tp2 = timePointFromString("Jun 27 2019 09:25:00", "%b %d %Y %H:%M:%S");
  // Serial.println(timePointToString(tp2).c_str());

  readStoredConfig();
  initializeWiFi();
  espTimer.initializeTimer();

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
  scheduler.runAvailableTasks(&espTimer);
}

void logInfo()
{
  static unsigned long lastStations = 0;
  int stations = WiFi.softAPgetStationNum();
  if (stations != lastStations)
  {
    lastStations = WiFi.softAPgetStationNum();
    Serial.printf("[ LOG    ] Stations connected = %d\n", stations);
  }
}