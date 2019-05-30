#include "Alarm.h"
#include <Arduino.h>
#include "pins_arduino.h"

Alarm::Alarm() {
	this->alarmState = 0;
}

Alarm::~Alarm() {
}

int Alarm::setAlarm(int sensorState) {

	if (sensorState == LOW) {
		digitalWrite(D0, LOW);
		return 0;
	}
	else {
		digitalWrite(D0, HIGH);
		return 1;
	}
}

int Alarm::turnOnAlarm() {
	digitalWrite(D0, HIGH);
	return 1;
}

int Alarm::turnOffAlarm() {
	digitalWrite(D0, LOW);
	return 0;
}
