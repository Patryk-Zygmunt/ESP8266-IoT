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

void Scheduler::addTask(Task task)
{
  tasks.push_back(task);
}

void Scheduler::runAvailableTasks(ITimer *timer)
{
  auto currentTime = timer->getTime();
  vector<Task> remainingTasks;

  std::vector<Task>::iterator iterator = tasks.begin();
  while (iterator != tasks.end()) {
	  if ((*iterator).executionTime < currentTime) {
		  (*iterator).execute();
	  }
	  else {
		  remainingTasks.push_back(*iterator);
	  }
	  iterator++;
  }

  tasks = remainingTasks;
}


