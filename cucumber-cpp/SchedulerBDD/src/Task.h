#ifndef _TASK_h
#define _TASK_h
#include <string>
#include "PinStateMock.h"

class Task {
	
public:
	static int counter;
	int id;
	int pin;
	double executionTime;
	int targetState;
	std::string name;
	Task();
	Task(std::string name, int pin, double executionTime, int targetState);
	~Task();
	bool execute(PinStateMock &pinstatemock);
	

};

#endif
