#include "ESPTimer.h"
#include "arduino.h"

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200);

ESPTimer::ESPTimer()
{
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
}
