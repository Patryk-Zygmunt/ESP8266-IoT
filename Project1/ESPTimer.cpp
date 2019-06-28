#include "ESPTimer.h"
#include "arduino.h"
#include "utils.h"
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200);

ESPTimer::ESPTimer()
{
    this->lastMillisTime = millis();
    this->lastLogTime = millis();
    this->currentTime = timePointFromString("Jun 27 2019 09:25:00", "%b %d %Y %H:%M:%S");
}
void ESPTimer::initializeTimer()
{
    // timeClient.begin();
    // delay(1000);
    // synchronizeTime();
}

void ESPTimer::synchronizeTime()
{
    // timeClient.update();
    // Serial.printf("[  TIMER ]  time: %s date:%s\n", timeClient.getFormattedTime().c_str(), timeClient.getFormattedDate().c_str());
}

chrono::system_clock::time_point ESPTimer::getTime()
{
    long millisSinceLastCheck = millis() - lastMillisTime;
    lastMillisTime = millis();
    currentTime += std::chrono::milliseconds(millisSinceLastCheck);
    logTime();
    return currentTime;
}

void ESPTimer::logTime()
{
    if (millis() - lastLogTime > 30000)
    {
        Serial.printf("[ TIMER  ] Time requested. Current time: %s\n", timePointToString(currentTime).c_str());
        lastLogTime = millis();
    }
}