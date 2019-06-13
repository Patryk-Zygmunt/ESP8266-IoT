#include "ArduinoJson.h"

#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::ostringstream

#include "GreetingProvider.h";
#include "LoginPageProvider.h";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

const char *ssid = "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
const char *password = "password";

const char *index_path = "/index.html";
const char *js_path = "/main.js";
const char *html = "text/html";
const char *js = "application/javascript";

ESP8266WebServer server(80);
LoginPageProvider loginProvider;

void setup()
{
  SPIFFS.begin();
  Serial.begin(115200);
  delay(2000);
  initializeWiFi();
  const char *headerkeys[] = {"User-Agent", "Cookie"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.on("/", handleRoot);
  server.on("/main.js", handleJs);
  server.on("/devices.html", handleJs);
  server.on("/scheduler", HTTP_POST, handlePostScheduler);
  server.on("/scheduler", HTTP_GET, handleGetScheduler);
  server.on("/loginPage", handleLoginPage);
  server.on("/doLogin", handleDoLogin);
  server.begin();
}

void initializeWiFi()
{
  ESP.eraseConfig();
  delay(2000);
  WiFi.mode(WIFI_AP);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("mDNS responder started");
  }
  else
  {
    Serial.println("Error setting up MDNS responder!");
  }
}

void loop()
{
  logInfo();
  server.handleClient();
}

void logInfo()
{
  static unsigned long lastStations = 0;
  int stations = WiFi.softAPgetStationNum();
  if (stations != lastStations)
  {
    lastStations = WiFi.softAPgetStationNum();
    ;
    Serial.printf("Stations connected = %d\n", stations);
  }
}

void handleJs()
{
  if (SPIFFS.exists(js_path))
  {
    File jsFile = SPIFFS.open(js_path, "r");
    size_t sent = server.streamFile(jsFile, js);
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", js_path, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", js_path);
  }
  handleGetScheduler();
}

void handleRoot()
{
  if (!checkIfAuthorized())
  {
    return;
  }

  if (SPIFFS.exists(index_path))
  {
    File indexFile = SPIFFS.open(index_path, "r");
    size_t sent = server.streamFile(indexFile, html);
    indexFile.close();
    Serial.printf("File %s sent, %d bytes\n", index_path, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", index_path);
  }
  // std::string contents = "hello from esp8266! <br/>" + loginProvider.getLogoutButton();
  // server.send(200, "text/html", contents.c_str());
}

void handlePostScheduler()
{
  if (!checkIfAuthorized())
  {
    return;
  }
  Serial.printf("POST /scheduler");
  StaticJsonDocument<256> doc;
  deserializeJson(doc, server.arg("plain"));
  JsonObject root = doc.as<JsonObject>();
  server.send(200, "text/html", "OK");

  // Examples
  Serial.println(server.arg("plain"));
  String pin = doc["pin"];
  String thing = doc["thing"];
  String date = doc["date"];
  String action = doc["action"];
  Serial.println(pin.c_str());
  Serial.println(thing.c_str());
  Serial.println(date.c_str());
  Serial.println(action.c_str());
}

void handleGetScheduler()
{
  if (!checkIfAuthorized())
  {
    return;
  }
  Serial.printf("GET /scheduler");

  StaticJsonDocument<400> doc;
  JsonArray array = doc.to<JsonArray>();
  JsonObject event1 = array.createNestedObject();
  event1["pin"] = "1";
  event1["thing"] = "thing_a";
  event1["date"] = "12-12-12";
  event1["action"] = "Turn on";
  JsonObject event2 = array.createNestedObject();
  event2["pin"] = "2";
  event2["thing"] = "thing_b";
  event2["date"] = "12-12-12";
  event2["action"] = "Turn off";
  JsonObject event3 = array.createNestedObject();
  event3["pin"] = "3";
  event3["thing"] = "thing_c";
  event3["date"] = "12-12-12";
  event3["action"] = "Turn on";

  String myString;
  serializeJson(array, myString);
  server.send(200, "text/json", myString);
}

void handleLoginPage()
{
  server.send(200, "text/html", loginProvider.getLoginPageContents().c_str());
}

void handleDoLogin()
{
  std::string inputLogin = toStdStr(server.arg("login"));
  std::string inputPassword = toStdStr(server.arg("password"));
  std::string token = loginProvider.validateUserData(inputLogin, inputPassword);
  Serial.println(inputLogin.c_str());
  Serial.println(inputPassword.c_str());
  if (token != "")
  {
    server.sendHeader("Location", "/");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", token.c_str());
    server.send(301);
    Serial.println("Log in Successful");
  }
  else
  {
    Serial.println("Invalid credentials login!");
    server.send(403, "text/html", loginProvider.getInvalidCredentialsPage().c_str());
  }
}

bool checkIfAuthorized()
{
  if (server.hasHeader("Cookie"))
  {
    std::string token = toStdStr(server.header("Cookie"));
    Serial.printf("Trying to access page with token: %s\n", token.c_str());
    bool tokenValid = loginProvider.isTokenValid(token);
    if (tokenValid)
    {
      Serial.printf("Access granted.\n");
      return true;
    }
  }
  Serial.printf("Access denied!\n");
  server.send(403, "text/html", loginProvider.getInvalidCredentialsPage().c_str());
  return false;
}

std::string toStdStr(String s)
{
  int str_len = s.length() + 1;
  char char_array[str_len];
  s.toCharArray(char_array, str_len);
  return std::string(char_array);
}
