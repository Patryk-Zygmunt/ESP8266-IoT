#include "Task.h"

int Task::counter = 0;

Task::Task()
{
}

Task::Task(std::string name, int pin, double executionTime, bool targetState)
{
	this->id = Task::counter++;
	this->name = name;
	this->pin = pin;
	this->executionTime = executionTime;
	this->targetState = targetState;
}



Task::~Task()
{
}

bool Task::execute() {

	//int pinState = digitalRead(this->pin);

	//digitalWrite(this->pin, this->targetState);

	return this->targetState;
}
