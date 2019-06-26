#include <FS.h>
#include <string>
#include "ArduinoJson.h"
#include "arduino.h"

#include "rest_handlers.h"
#include "server.h"
#include "utils.h"
#include "init.h"
#include "login_service.h"

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
        File file = SPIFFS.open(CONFIG_PATH, "w");
        file.println(ssid);
        file.println(wifiPass);
        file.println(user);
        file.println(userPass);
        file.println(mode);
        file.close();
        sendAlert("OK", "All data has been updated. Board will restart now...", "/", 5);
        delay(3000);
        ESP.reset();
    }
}

void handlePostScheduler()
{
    if (!checkIfAuthorized())
    {
        return;
    }
    Serial.printf("[ SERVER ] POST /scheduler\n");
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
    Serial.printf("[ SERVER ] GET /scheduler\n");

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

void handleDoLogin()
{
    std::string inputLogin = toStdStr(server.arg("login"));
    std::string inputPassword = toStdStr(server.arg("password"));
    std::string token = loginProvider.validateUserData(inputLogin, inputPassword);
    trim(inputLogin);
    trim(inputPassword);
    trim(token);

    Serial.printf("[ SERVER ] DEBUG: Logging in as %s:%s\n", inputLogin.c_str(), inputPassword.c_str());
    if (token != "")
    {
        server.sendHeader("Location", "/");
        server.sendHeader("Cache-Control", "no-cache");
        server.sendHeader("Set-Cookie", token.c_str());
        server.send(301);
        Serial.println("[ SERVER ] Log in Successful");
    }
    else
    {
        Serial.println("[ SERVER ] Invalid credentials login!");
        sendAlert("Error", "Access denied!", "/loginPage", 3);
    }
}
