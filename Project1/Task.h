#ifndef _TASK_h
#define _TASK_h

class Task {
	
public:
	static long counter;
	int id;
	int pin;
	double executionTime;
	bool targetState;
	std::string name;
	Task(int pin, double executionTime, bool targetState);
	~Task();
	bool execute();
	

};

#endif