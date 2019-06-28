#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <sstream>

#include "wifi.h"
#include "init.h"
#include "utils.h"

const int MAX_WIFI_INIT_ATTEMPTS = 4;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);
DNSServer dnsServer;

void initializeWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPdisconnect(true);
    delay(1000);

    ESP.eraseConfig();
    delay(2000);

    if (WIFI_MODE == 0)
    {
        Serial.printf("[ WiFi   ] Setting soft-AP ... (%s:%s) \n", WIFI_SSID.c_str(), WIFI_PASS.c_str());
        WiFi.mode(WIFI_AP);
        WiFi.softAPConfig(apIP, apIP, netMsk);

        boolean softApStarted = (WIFI_PASS.empty())
                                    ? WiFi.softAP(WIFI_SSID.c_str())
                                    : WiFi.softAP(WIFI_SSID.c_str(), WIFI_PASS.c_str());
        delay(100);

        // captive portal
        dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
        dnsServer.start(53, "*", apIP);
        delay(10E3);

        Serial.println(softApStarted ? "[ WiFi   ] Ready" : "[ WiFi   ] Failed!");
        if (!softApStarted)
        {
            Serial.println("[ WiFi   ] Unable to start Access Point. Board will return to factory settings."); // should reset?
            doHardReset();
        }
        Serial.print("[ WiFi   ] IP address: ");
        Serial.println(WiFi.softAPIP());

        if (MDNS.begin("esp8266"))
        {
            Serial.println("[ WiFi   ] mDNS responder started");
        }
        else
        {
            Serial.println("[ WiFi   ] Error setting up MDNS responder!");
        }
    }
    else
    {
        WiFi.mode(WIFI_STA);
        Serial.printf("[ WiFi   ] Connecting to %s", WIFI_SSID.c_str());
        WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());

        int wifiInitAttempts = 0;
        while (wifiInitAttempts < MAX_WIFI_INIT_ATTEMPTS)
        {
            for (int i = 0; i < 10; i++)
            {
                delay(500);
                Serial.print(".");
            }
            Serial.println();
            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.println("[ WiFi   ]  connected");
                Serial.print("[ WiFi   ] IP address:\t");
                Serial.println(WiFi.localIP());
                break;
            }

            else
            {
                wifiInitAttempts++;
                Serial.println("[ WiFi   ] Failed to connect. Retrying...");
                if (wifiInitAttempts >= MAX_WIFI_INIT_ATTEMPTS)
                {
                    Serial.println("[ WiFi   ] Unable to connect to configured WiFi network. Board will return to factory settings."); // should reset?
                    doHardReset();
                }
            }
        }
    }
}

std::string getNetworksInHtml()
{
    std::stringstream ss;

    int numberOfNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numberOfNetworks; i++)
    {
        Serial.printf("[ WiFi   ] Network found: %s (%s dBm)\n", toStdStr(WiFi.SSID(i)).c_str(), toStdStr(String(WiFi.RSSI(i))).c_str());
        ss << WiFi.SSID(i).c_str() << " (" << WiFi.RSSI(i) << " dBm) <br />";
    }
    return ss.str();
}