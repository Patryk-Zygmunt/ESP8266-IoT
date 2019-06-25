#include <string>
#include <iostream>
#include <sstream>
#include <FS.h>

#include "utils.h"
#include "init.h"

const char *CONFIG_PATH = "/config.txt";

std::string WIFI_SSID = "AAA_NODEMCU";
std::string WIFI_PASS = "AAA_NODEMCU";
int WIFI_MODE = 0;

void readStoredConfig()
{
    if (SPIFFS.exists(CONFIG_PATH))
    {
        Serial.println();
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

        WIFI_SSID = ssid;
        WIFI_PASS = wifiPass;

        Serial.println(configContents.c_str());

        String modeFromCfg = String(char(config.read()));
        modeFromCfg.replace("/n", "");
        if (toStdStr(modeFromCfg).find("AP") == 1)
        {
            WIFI_MODE = 0;
        }
        else
        {
            WIFI_MODE = 1;
        }
    }
    else
    {
        Serial.print("config file does not exist - starting with default config");
    }
}

boolean configPresent() {
    return !SPIFFS.exists(CONFIG_PATH);
}