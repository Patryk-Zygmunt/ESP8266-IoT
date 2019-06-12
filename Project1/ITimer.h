#ifndef _TIMER_h
#define _TIMER_h

class ITimer {
public:
	virtual long getTime() = 0;
	virtual long getOffset() = 0;

	ITimer();
	~ITimer();
};