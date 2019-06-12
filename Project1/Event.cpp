#include "Event.h"

Event::Event(int pin, int hour){  
  this->eventPin = pin;
  this->eventHour = hour; 
}


int Event::getPin() {
  return this->eventPin;
}

int Event::getHour() {
  return this->eventHour;  
}
