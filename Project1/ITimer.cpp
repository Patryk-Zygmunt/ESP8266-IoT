#include "ITimer.h"
#include "Arduino.h"



ITimer::ITimer()
{
}


ITimer::~ITimer()
{
}

void ITimer::updateCurrentTime() {
	currentTime = inputTime + millis() - offsetTime;
}
