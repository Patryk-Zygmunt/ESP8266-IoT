#include <string>
#include <FS.h>
#include <sstream>

#include "dynamic_file_handlers.h"
#include "server.h"
#include "utils.h"
#include "wifi.h"

const char *ALERT_PATH = "/alert.html";
const char *INIT_PATH = "/init.html";

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
        Serial.printf("[ SERVER ] File %s sent\n", ALERT_PATH);
        return true;
    }
    else
    {
        Serial.printf("[ SERVER ] %s does not exist\n", ALERT_PATH);
        return false;
    }
}

void handleInit()
{
        if (SPIFFS.exists(INIT_PATH))
    {
        File alertFile = SPIFFS.open(INIT_PATH, "r");
        String fileContents;
        while (alertFile.available())
        {
            String line = String(char(alertFile.read()));
            fileContents += line.c_str();
        }
        alertFile.close();
        fileContents.replace("%NETWORKS%", String(getNetworksInHtml().c_str()));

        server.send(400, "text/html", fileContents);
        Serial.printf("[ SERVER ] File %s sent\n", INIT_PATH);
    }
    else
    {
        Serial.printf("[ SERVER ] %s does not exist\n", INIT_PATH);
    }
}

