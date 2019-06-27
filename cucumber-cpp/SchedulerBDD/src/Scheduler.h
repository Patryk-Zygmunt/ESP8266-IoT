#ifndef _SCHEDULER_h
#define _SCHEDULER_h
#include <vector>
#include "Task.h"
#include "ITimer.h"

class Scheduler {

private:
	
public:
	std::vector <Task> tasks;
	Scheduler();
	~Scheduler();
	void addTask(Task task);
	bool runAvailableTasks(ITimer timer, PinStateMock &pinstatemock);
	bool finalizeTask(Task task);
	bool finalizeTask(int taskId);

};

#endif
