#ifndef _SCHEDULER_h
#define _SCHEDULER_h

class Scheduler {

private:
	
public:
	std::vector <Task> tasks;
	Scheduler();
	~Scheduler();
	//void addTask(int delayTime, int pin);
	void addTask(Task task);
	void runAvailableTasks(ITimer timer);
	bool finalizeTask(Task task);
	

};

#endif