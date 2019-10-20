#include "KeyEvent.h"

#include <string>

KeyEvent::KeyEvent(std::string d) : direction(d) {}

std::string KeyEvent::ToStr() {
  return "KEYEVENT: " + direction;
}
