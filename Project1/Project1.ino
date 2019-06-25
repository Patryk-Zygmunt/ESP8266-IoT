#include <string>
#include <iostream>
#include <sstream>

#include "ArduinoJson.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "GreetingProvider.h";
#include "LoginPageProvider.h";

#include "init.cpp";

const char *INDEX_PATH = "/index.html";
const char *JS_PATH = "/main.js";
const char *LOGIN_PATH = "/login.html";
const char *INIT_PATH = "/init.html";
const char *ALERT_PATH = "/alert.html";
const char *HTML_CONTENT = "text/html";
const char *JS_CONTENT = "application/javascript";
const int MAX_WIFI_INIT_ATTEMPTS = 1;

uint8_t RESET_PIN = D3; //GPIO0, flash button

ESP8266WebServer server(80);
LoginPageProvider loginProvider;

void setup()
{
  pinMode(RESET_PIN, INPUT);
  SPIFFS.begin();
  Serial.begin(115200);
  delay(2000);

  readStoredConfig();

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
  server.on("/init", handleInit);
  server.on("/doInit", HTTP_POST, handleDoInit);
  // server.on("/devices.html", handleJs);
  server.on("/scheduler", HTTP_POST, handlePostScheduler);
  server.on("/scheduler", HTTP_GET, handleGetScheduler);
  server.on("/loginPage", handleLoginPage);
  server.on("/doLogin", handleDoLogin);
  server.begin();
  delay(3000);
}

void initializeWiFi()
{
  ESP.eraseConfig();
  delay(2000);

  if (WIFI_MODE == 0)
  {
    WiFi.mode(WIFI_AP);
    Serial.println();
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(WIFI_SSID.c_str(), WIFI_PASS.c_str()) ? "Ready" : "Failed!");
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
  else
  {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s", WIFI_SSID.c_str());
    WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());

    int wifiInitAttempts = 0;
    while (wifiInitAttempts < MAX_WIFI_INIT_ATTEMPTS)
    {
      for (int i = 0; i < 10; i++)
      {
        delay(500);
        Serial.print(".");
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println(" connected");
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
        break;
      }

      else
      {
        wifiInitAttempts++;
        Serial.print("Failed to connect.");
        if (wifiInitAttempts >= MAX_WIFI_INIT_ATTEMPTS)
        {
          Serial.println("Unable to connect to configured WiFi network. "); // should reset?
          doHardReset();
        }
      }
    }
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
      doHardReset();
  }
}

void doHardReset()
{
  Serial.println("Resetting...");
  SPIFFS.remove(CONFIG_PATH);
  ESP.reset();
}

void logInfo()
{
  static unsigned long lastStations = 0;
  int stations = WiFi.softAPgetStationNum();
  if (stations != lastStations)
  {
    lastStations = WiFi.softAPgetStationNum();
    Serial.printf("Stations connected = %d\n", stations);
  }
}

void handleInit()
{
  if (SPIFFS.exists(INIT_PATH))
  {
    File initFile = SPIFFS.open(INIT_PATH, "r");
    size_t sent = server.streamFile(initFile, HTML_CONTENT);
    initFile.close();
    Serial.printf("File %s sent, %d bytes\n", INIT_PATH, sent);
  }
  else
  {
    Serial.printf("%s does not exist\n", JS_PATH);
    sendAlert("Error", "An error occured!", "/", 3);
  }
}

void handleDoInit()
{
  if (SPIFFS.exists(CONFIG_PATH))
  {
    sendAlert("Error", "Access denied!", "/", 3);
    return;
  }
  else
  {
    String ssid = server.arg("ssid");
    String wifiPass = server.arg("wifi_password");
    String user = server.arg("user");
    String userPass = server.arg("user_password");
    String mode = server.arg("mode");
    Serial.print("asdf");
    File file = SPIFFS.open(CONFIG_PATH, "w");
    file.println(ssid);
    file.println(wifiPass);
    file.println(user);
    file.println(userPass);
    file.println(mode);
    file.close();
    sendAlert("OK", "All data has been updated. Board will restart now...", "/", 5);
    ESP.reset();
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
  if (configPresent())
  {
    handleInit();
    return;
  }

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
