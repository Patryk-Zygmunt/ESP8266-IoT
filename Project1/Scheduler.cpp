#include "Scheduler.h"


Scheduler::Scheduler(){  
}

bool Scheduler::nextStep(int currentHour, int eventNum) {
  
  int eHour  = this->eventsList.at(eventNum).getHour();
  if(currentHour == eHour){
    return true;  
  }
  return false;  
}

void Scheduler::addEvent(Event e) {
  this->eventsList.push_back(e);  
}
