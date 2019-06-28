#pragma once
#include "ITimer.h"
#include <vector>

class FakeTimer :
	public ITimer {
public:
	vector<chrono::system_clock::time_point> timePoints;

	FakeTimer(vector<chrono::system_clock::time_point> timePoints);
	~FakeTimer();
	virtual chrono::system_clock::time_point getTime();
};

