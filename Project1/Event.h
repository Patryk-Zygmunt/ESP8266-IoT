#ifndef _EVENT_h
#define _EVENT_h

class Event {
 private:
  int eventPin;
  int eventHour; 
 public:
  Event(int pin, int hour);
  int getPin();
  int getHour();
};


#endif
