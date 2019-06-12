#ifndef _TIMER_h
#define _TIMER_h

class ITimer {
public:
	double inputTime;
	double  offsetTime;
	double  currentTime;

	double  updateCurrentTime();

	ITimer();
	~ITimer();
};