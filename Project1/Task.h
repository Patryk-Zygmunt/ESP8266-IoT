#ifndef _TASK_h
#define _TASK_h
#include <string>

class Task {
	
public:
	static int counter;
	int id;
	int pin;
	double executionTime;
	bool targetState;
	std::string name;
	Task(std::string name, int pin, double executionTime, bool targetState);
	~Task();
	bool execute();
	

};

#endif
