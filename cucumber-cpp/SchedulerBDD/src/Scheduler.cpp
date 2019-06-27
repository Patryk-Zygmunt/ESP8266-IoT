#include "Scheduler.h"
#include <vector>
#include "Task.h"
#include "ITimer.h"
using namespace std;
vector<Task> tasks;
Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::addTask(Task task) {
	tasks.push_back(task);
}

bool Scheduler::finalizeTask(Task task) {
  bool found = false;
  vector <Task>::iterator iterator;
  for (iterator = tasks.begin(); iterator != tasks.end(); ++iterator) {
    if ((*iterator).id == task.id) {
      iterator = tasks.erase(iterator);
      --iterator;
      found = true;
    }
  }
  return found;
}

bool Scheduler::finalizeTask(int taskId) {
  bool found = false;
  vector <Task>::iterator iterator;
  for (iterator = tasks.begin(); iterator != tasks.end(); ++iterator) {
    if ((*iterator).id == taskId) {
      iterator = tasks.erase(iterator);
      --iterator;
      found = true;
    }
  }
  return found;
}

bool Scheduler::runAvailableTasks(ITimer timer, PinStateMock &pinstatemock) {
	std::vector <Task>::iterator iterator;
	timer.updateCurrentTime();
	bool executed = false;
  
	for (iterator = tasks.begin(); iterator != tasks.end(); ++iterator) {
		if ((*iterator).executionTime < timer.currentTime) {
			(*iterator).execute(pinstatemock);
			int taskId = (*iterator).id;
			taskId = taskId;
			return executed;

			//executed = finalizeTask(taskId);
		}
	}
	return executed;
}
