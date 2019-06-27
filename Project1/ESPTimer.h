#include "ITimer.h"
#include <chrono>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

using namespace std;

// extern WiFiUDP ntpUDP;
// extern NTPClient timeClient;

class ESPTimer : public ITimer
{
public:
    chrono::system_clock::time_point currentTime;

    ESPTimer();
    void initializeTimer();
    void synchronizeTime();
    virtual chrono::system_clock::time_point getTime();
};
