#ifndef _TIMER_h
#define _TIMER_h
#include <chrono>

using namespace std;

class ITimer {
public:
	virtual chrono::system_clock::time_point getTime() = 0;
};
#endif
