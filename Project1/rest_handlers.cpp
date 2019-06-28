#include <FS.h>
#include <string>
#include "ArduinoJson.h"
#include "arduino.h"

#include "rest_handlers.h"
#include "server.h"
#include "utils.h"
#include "init.h"
#include "login_service.h"
#include "scheduler_service.h"
#include "Task.h"
#include "time_service.h"

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

String getTasksAsJson()
{
    StaticJsonDocument<500> doc;
    JsonArray array = doc.to<JsonArray>();

    std::vector<Task>::iterator iterator = scheduler.tasks.begin();
    while (iterator != scheduler.tasks.end())
    {
        std::string date = timePointToString((*iterator).executionTime, "%Y-%m-%d %H:%M");
        Serial.printf("DYTA: %s\n", date.c_str());
        JsonObject event1 = array.createNestedObject();
        event1["pin"] = (*iterator).pin.c_str();
        event1["thing"] = (*iterator).name.c_str();
        event1["date"] = date.c_str(); // BUG
        event1["action"] = (*iterator).actionName.c_str();
        iterator++;
    }
    String tasksAsJson;
    serializeJson(array, tasksAsJson);
    Serial.println("JSON");
    Serial.println(tasksAsJson.c_str());
    Serial.println("JSON");
    return tasksAsJson;
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

    // Parse task
    String pin = doc["pin"];
    String thing = doc["thing"];
    String date = doc["date"];
    String action = doc["action"];
    Serial.printf("[ SERVER ] Incoming task %s:%s:%s:%s\n", pin.c_str(), thing.c_str(), date.c_str(), action.c_str());

    std::chrono::system_clock::time_point tp = timePointFromString(toStdStr(date), "%Y-%m-%dT%H:%M");

    Task task(toStdStr(thing), tp, [thing, tp]() {
        Serial.printf("[ TASK   ] Executing scheduled task %s. Timestamp: %s\n", thing.c_str(), timePointToString(tp).c_str());
        // change pin state here, after adding mapping
    },
              toStdStr(pin), toStdStr(action));
    scheduler.addTask(task);

    String tasksAsJson = getTasksAsJson();
    server.send(200, "text/json", tasksAsJson);
}

void handleGetScheduler()
{
    if (!checkIfAuthorized())
    {
        return;
    }
    Serial.printf("[ SERVER ] GET /scheduler\n");

    String tasksAsJson = getTasksAsJson();
    server.send(200, "text/json", tasksAsJson);
}

void handleDoLogin()
{
    std::string inputLogin = toStdStr(server.arg("login"));
    std::string inputPassword = toStdStr(server.arg("password"));
    std::string token = loginProvider.validateUserData(inputLogin, inputPassword);
    std::string timestamp = toStdStr(server.arg("timestamp"));
    Serial.printf("login timestamp: %s\n", timestamp.c_str());
    espTimer.currentTime = timePointFromString(timestamp.c_str());

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
