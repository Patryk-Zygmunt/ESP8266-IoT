#include "GreetingProvider.h";
#include <Arduino.h>;
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
const char* password = "password";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
  server.on("/", handleRoot);
//  server.on("/loginPage", handleLoginPage);
//  server.on("/doLogin", handleDoLogin);
//  server.on("/cokolwiekInnego", handleCokolwiekInnego);


}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

//void handleLoginPage() {
//  server.send(200, "text/plain", loginProvider.getLoginPageContents());
//}
//
//void handleDoLogin() {
//  // tutaj jakoś wyciągamy z POSTa dane logowania
//  std::string token = loginProvider.authenticate(user, pass);
//  if (token jest niepusty, znaczy login i hasło ok) {
//    server.send("200", "text/plain", token);
//  }
//}
//
//void handleCokolwiekInnego() {
//  std::string token = //wyciągamy token z zapytania jakoś
//  if (!loginProvider.isTokenValid(token)) {
//    server.send(403, "text/plain", "brak dostępu");
//  }
}
