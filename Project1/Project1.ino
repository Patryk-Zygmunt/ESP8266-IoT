#include "ArduinoJson.h"

#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::ostringstream

#include "GreetingProvider.h";
#include "LoginPageProvider.h";
#include "Scheduler.h";
#include "Task.h";
#include "ITimer.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

const char *ssid = "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
const char *password = "password";

const char *INDEX_PATH = "/index.html";
const char *JS_PATH = "/main.js";
const char *LOGIN_PATH = "/login.html";
const char *ALERT_PATH = "/alert.html";
const char *HTML_CONTENT = "text/html";
const char *JS_CONTENT = "application/javascript";

uint8_t RESET_PIN = D3; //GPIO0, flash button

ESP8266WebServer server(80);
LoginPageProvider loginProvider;
Scheduler scheduler;

void setup()
{
  pinMode(RESET_PIN, INPUT);
  SPIFFS.begin();
  Serial.begin(115200);
  delay(2000);
  initializeWiFi();
  const char *headerkeys[] = {"User-Agent", "Cookie"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.on("/", handleRoot);
  server.on("/main.js", handleMainJs);
  server.on("/axios.min.js", handleAxiosJs);
  server.on("/moment.min.js", handleMomentJs);
  server.on("/jquery-3.3.1.slim.min.js", handleJqueryJs);
  server.on("/bootstrap.min.css", handleBootstrap);

  // server.on("/devices.html", handleJs);
  server.on("/scheduler", HTTP_POST, handlePostScheduler);
  server.on("/scheduler", HTTP_GET, handleGetScheduler);
  server.on("/loginPage", handleLoginPage);
  server.on("/doLogin", handleDoLogin);
  server.on("/addTask", handleAddTask);
  server.begin();
  delay(3000);
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
  handleReset();
  logInfo();
  server.handleClient();
}

void handleReset()
{
  if (digitalRead(RESET_PIN) == 0)
  {
    delay(5000);
    if (digitalRead(RESET_PIN) == 0)
    {
      Serial.println("Resetting...");
      ESP.reset();
    }
  }
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

void handleMainJs()
{
  if (SPIFFS.exists(JS_PATH))
  {
    File jsFile = SPIFFS.open(JS_PATH, "r");
    size_t sent = server.streamFile(jsFile, JS_CONTENT);
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", JS_PATH, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", JS_PATH);
  }
}

void handleAxiosJs()
{
  char *file = "/axios.min.js";
  if (SPIFFS.exists(file))
  {
    File jsFile = SPIFFS.open(file, "r");
    size_t sent = server.streamFile(jsFile, JS_CONTENT);
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", file, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", file);
  }
}

void handleMomentJs()
{
  char *file = "/moment.min.js";
  if (SPIFFS.exists(file))
  {
    File jsFile = SPIFFS.open(file, "r");
    size_t sent = server.streamFile(jsFile, JS_CONTENT);
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", file, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", file);
  }
}

void handleJqueryJs()
{
  char *file = "/jquery-3.3.1.slim.min.js";
  if (SPIFFS.exists(file))
  {
    File jsFile = SPIFFS.open(file, "r");
    size_t sent = server.streamFile(jsFile, JS_CONTENT);
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", file, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", file);
  }
}

void handleBootstrap()
{
  char *file = "/bootstrap.min.css";
  if (SPIFFS.exists(file))
  {
    File jsFile = SPIFFS.open(file, "r");
    size_t sent = server.streamFile(jsFile, "text/css");
    jsFile.close();
    Serial.printf("File %s sent, %d bytes\n", file, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", file);
  }
}

void handleRoot()
{
  if (!checkIfAuthorized())
  {
    return;
  }

  if (SPIFFS.exists(INDEX_PATH))
  {
    File indexFile = SPIFFS.open(INDEX_PATH, "r");
    size_t sent = server.streamFile(indexFile, HTML_CONTENT);
    indexFile.close();
    Serial.printf("File %s sent, %d bytes\n", INDEX_PATH, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", INDEX_PATH);
  }
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
  server.send(200, HTML_CONTENT, "OK");

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
  if (SPIFFS.exists(LOGIN_PATH))
  {
    File loginFile = SPIFFS.open(LOGIN_PATH, "r");
    size_t sent = server.streamFile(loginFile, HTML_CONTENT);
    loginFile.close();
    Serial.printf("File %s sent, %d bytes\n", LOGIN_PATH, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", LOGIN_PATH);
  }
  // server.send(200, "text/html", loginProvider.getLoginPageContents().c_str());
}

void handleDoLogin()
{
  std::string inputLogin = toStdStr(server.arg("login"));
  std::string inputPassword = toStdStr(server.arg("password"));
  std::string token = loginProvider.validateUserData(inputLogin, inputPassword);
  Serial.println(token.c_str());
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
    sendAlert("Error", "Invalid credentials!", "/loginPage", 3);
  }
}

boolean sendAlert(String header, String contents, String redirect, int delay)
{
  if (SPIFFS.exists(ALERT_PATH))
  {
    File alertFile = SPIFFS.open(ALERT_PATH, "r");
    String fileContents;
    while (alertFile.available())
    {
      String line = String(char(alertFile.read()));
      fileContents += line.c_str();
    }
    alertFile.close();
    fileContents.replace("%TIME%", String(delay));
    fileContents.replace("%REDIRECT%", redirect);
    fileContents.replace("%HEADER%", header);
    fileContents.replace("%CONTENT%", contents);

    Serial.println(fileContents);
    server.send(400, "text/html", fileContents);
    Serial.printf("File %s sent\n", ALERT_PATH);
    return true;
  }
  else
  {
    Serial.printf("%s does not exist\n", ALERT_PATH);
    return false;
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
  sendAlert("Error", "Invalid credentials!", "/loginPage", 3);
  return false;
}

std::string toStdStr(String s)
{
  int str_len = s.length() + 1;
  char char_array[str_len];
  s.toCharArray(char_array, str_len);
  return std::string(char_array);
}



void handleAddTask()
{
  Task task(toStdStr(server.arg("name")),
            server.arg("pin").toInt(),
            server.arg("executionTime").toDouble(),
            server.arg("targetState").compareTo("true") == 0 ? true : false);
  scheduler.addTask(task);
}
