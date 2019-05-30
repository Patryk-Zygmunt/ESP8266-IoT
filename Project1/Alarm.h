#pragma once

#include <string>

#ifndef ALARM
#define ALARM

class Alarm {

private:
	int alarmState;
public:
	Alarm();
	~Alarm();
	int setAlarm(int sensorState);
	int turnOnAlarm();
	int turnOffAlarm();
};

#endif

