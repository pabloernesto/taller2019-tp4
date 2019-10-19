#ifndef EVENT_H_
#define EVENT_H_

#include <string>

class Event {
  public:
  static Event* FromStr(std::string s);
  virtual std::string ToStr() = 0;
};

class KeyEvent : public Event {
  std::string direction;
  
  public:
  KeyEvent(std::string d);
  std::string ToStr();
};

#endif  // EVENT_H_
