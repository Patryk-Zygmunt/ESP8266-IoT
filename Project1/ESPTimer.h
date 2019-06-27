#include "ITimer.h"
#include <chrono>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

using namespace std;


class ESPTimer : public ITimer
{
public:
    chrono::system_clock::time_point currentTime;
    long lastMillisTime;
    long lastLogTime;

    ESPTimer();
    void initializeTimer();
    void synchronizeTime();
    void logTime();
    chrono::system_clock::time_point getTime();
};
