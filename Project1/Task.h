#ifndef _TASK_h
#define _TASK_h

class Task {

private:
	static long counter;
	int id;
	int pin;
	long executionTime;
	bool targetState;
public:
	Task(int pin, long executionTime, bool targetState);
	~Task();
	bool execute();

};

#endif