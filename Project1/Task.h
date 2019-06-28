#ifndef _TASK_h
#define _TASK_h
#include <string>
#include <functional>
#include <chrono>

using namespace std;

class Task {

public:
	static int counter;
	int id;
	string name;
	function<void()> action;
	string pin;
	string actionName;
	chrono::system_clock::time_point executionTime;

	Task(string name, chrono::system_clock::time_point executionTime, function<void()> action, string pin = "?", string actionName = "action");

	~Task();

	void execute();
};
#endif