#include "Scheduler.h"

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
}

void addTask(Task task) {
	tasks.push_back(task);
}

bool runAvailableTasks(ITimer timer) {
	vector <Task>::iterator iterator;
	timer.updateCurrentTime();
	bool executed;
	for (iterator = tasks.begin(); iterator != tasks.end(); ++iterator) {
		if (iterator->executionTime < timer->currentTime) {
			iterator.execute();
			executed = this->finalizeTask(iterator);
		}
	}
	return executed;
}

bool finalizeTask(Task task) {
	bool found = false;
	vector <Task>::iterator iterator;
	for (iterator = tasks.begin(); iterator != tasks.end(); ++iterator) {
		if (iterator->id == task->id) {
			iterator = tasks.erase(iterator);
			--iterator;
			found = true;
		}
	}
	return found;
}