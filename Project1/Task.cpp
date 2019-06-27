#include "Task.h"
#include <functional>
#include <chrono>

using namespace std;

int Task::counter = 0;

Task::Task(string name, chrono::system_clock::time_point executionTime, function<void()> action)
{
	this->id = Task::counter++;
	this->name = name;
	this->executionTime = executionTime;
	this->action = action;
}

Task::~Task()
{
}

void Task::execute() {
	action();
}
