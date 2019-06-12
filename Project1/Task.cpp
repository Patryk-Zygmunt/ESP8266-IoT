#include "Task.h"
#include "Arduino.h"

Task::Task(std::string name, int pin, double executionTime, bool targetState)
{
	this->id = this->counter++;
	this->name = name;
	this->pin = pin;
	this->executionTime = executionTime;
	this->targetState = targetState;
}

Task::~Task()
{
}

bool execute() {

	int pinState = digitalRead(this->pin);

	digitalWrite(this->pin, this->targetState);

	return this->targetState;
}