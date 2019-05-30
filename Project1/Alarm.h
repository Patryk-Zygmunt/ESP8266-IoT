#ifndef _ALARM_h
#define _ALARM_h

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