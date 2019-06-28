#include "Task.h"
#include <functional>
#include <chrono>

using namespace std;

int Task::counter = 0;

Task::Task(string name, chrono::system_clock::time_point executionTime, function<void()> action, string pin, string actionName)
{
	this->id = Task::counter++;
	this->name = name;
	this->executionTime = executionTime;
	this->action = action;
	this->pin = pin;
	this->actionName = actionName;
}

Task::~Task()
{
}

void Task::execute() {
	action();
}
