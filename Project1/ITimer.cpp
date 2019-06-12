#include "ITimer.h"



ITimer::ITimer()
{
}


ITimer::~ITimer()
{
}

void updateCurrentTime() {
	this->currentTime = this->inputTime + millis() - this->offsetTime;
}
