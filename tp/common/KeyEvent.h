#ifndef KEYEVENT_H_
#define KEYEVENT_H_
#include "Event.h"
#include <string>

class KeyEvent : public Event {
  std::string direction;
  
  public:
  KeyEvent(std::string d);
  std::string ToStr();
};

#endif