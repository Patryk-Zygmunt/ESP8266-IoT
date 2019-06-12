#include "GreetingProvider.h";
#include "LoginPageProvider.h";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
const char *password = "password";

ESP8266WebServer server(80);
LoginPageProvider loginProvider;
Scheduler scheduler;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  initializeWiFi();
  const char *headerkeys[] = {"User-Agent", "Cookie"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.on("/", handleRoot);
  server.on("/loginPage", handleLoginPage);
  server.on("/doLogin", handleDoLogin);
  server.on("/addTask", handleAddTask);
  server.on("/deleteTask", handleDeleteTask);
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

void handleRoot()
{
  if (!checkIfAuthorized())
  {
    return;
  }
  std::string contents = "hello from esp8266! <br/>" + loginProvider.getLogoutButton();
  server.send(200, "text/html", contents.c_str());
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
    server.send(403, "text/html", loginProvider.getInvalidCredentialsPage().c_str());
  }
}

bool checkIfAuthorized()
{
  if (server.hasHeader("Cookie"))
  {
    std::string token = toStdStr(server.header("Cookie"));
    Serial.printf("Trying to access page with token: %s", token.c_str());
    bool tokenValid = loginProvider.isTokenValid(token);
    if (tokenValid)
    {
      Serial.printf("Access granted.");
      return true;
    }
  }
  Serial.printf("Access denied!");
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



void handleAddTask()
{
  Task task;
  task.name = toStdStr(server.arg("name"));
  task.pin = server.arg("pin").toInt();
  task.executionTime = server.arg("executionTime").toDouble();
  task.targetState = server.arg("targetState").compareTo("true") == 0 ? true : false;

  scheduler.addTask(task);
}