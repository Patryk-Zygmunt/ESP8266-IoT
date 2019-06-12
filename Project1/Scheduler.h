#ifndef _SCHEDULER_h
#define _SCHEDULER_h
#include "Event.h"
#include <vector>

class Scheduler {
 public:
  std::vector <Event> eventsList;
  
  Scheduler();
  void addEvent(Event e);
  bool nextStep(int currentHour, int eventNum);
  
};

#endif
