#include <string>
#include <iostream>
#include <sstream>
#include <FS.h>

#include "utils.h"
#include "init.h"
#include "login_service.h"

const char *CONFIG_PATH = "/config.txt";
std::string WIFI_SSID = "A_NODEMCU";
std::string WIFI_PASS = "";
int WIFI_MODE = 0;
extern uint8_t RESET_PIN = D3; //GPIO0, flash button
extern uint8_t LED_PIN = D0;   //GPIO16, built-in led

void readStoredConfig()
{
    if (SPIFFS.exists(CONFIG_PATH))
    {
        File config = SPIFFS.open(CONFIG_PATH, "r");
        std::string configContents = "";
        while (config.available())
        {
            configContents += char(config.read());
        }
        std::stringstream ss(configContents);

        std::string ssid;
        std::string wifiPass;
        std::string user;
        std::string userPass;
        std::string mode;

        std::getline(ss, ssid);
        std::getline(ss, wifiPass);
        std::getline(ss, user);
        std::getline(ss, userPass);
        std::getline(ss, mode);

        trim(ssid);
        trim(wifiPass);
        trim(user);
        trim(userPass);

        WIFI_SSID = ssid.c_str();
        WIFI_PASS = wifiPass.c_str();
        loginProvider.setCredentials(user, userPass);
        Serial.printf("[  INIT  ] New credentials: %s:%s\n", user.c_str(), userPass.c_str());

        Serial.printf("[  INIT  ] Config file contents:\n"); //TODO: remove for final release
        Serial.println(configContents.c_str());

        WIFI_MODE = mode.find("AP") == std::string::npos ? 1 : 0;
        Serial.printf("[  INIT  ] WiFi mode determined as %d (0 - ap, 1 - sta).\n", WIFI_MODE);
    }
    else
    {
        Serial.printf("[  INIT  ] Config file does not exist - starting with default config.\n");
    }
}

boolean configPresent()
{
    return !SPIFFS.exists(CONFIG_PATH);
}

void handleReset()
{
    if (digitalRead(RESET_PIN) == 0)
    {
        delay(5000);
        if (digitalRead(RESET_PIN) == 0)
        {
            digitalWrite(LED_PIN, LOW);
            delay(3000);
            digitalWrite(LED_PIN, HIGH);
            doHardReset();
        }
    }
}

void doHardReset()
{
    Serial.println("[  INIT  ] Resetting...");
    SPIFFS.remove(CONFIG_PATH);
    ESP.reset();
}