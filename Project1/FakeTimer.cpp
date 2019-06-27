#include "FakeTimer.h"

FakeTimer::FakeTimer(vector<chrono::system_clock::time_point> timePoints) {
	this->timePoints = timePoints;
}

FakeTimer::~FakeTimer() {
}

chrono::system_clock::time_point FakeTimer::getTime() {
	auto firstPoint = timePoints.front();
	auto firstElementPointer = timePoints.begin();
	timePoints.erase(firstElementPointer);
	return firstPoint;
}
