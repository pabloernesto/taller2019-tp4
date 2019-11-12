#include "Button.h"
#include <string>

Button::Button(std::string name, int width, int height, Race* race) : name(name),
  button({0, 0, width * (int) name.size(), height}), race(race) {}

Button::~Button() {
}

std::string Button::GetName(){
  return name; 
}

void Button::SetPosition(int x, int y){
  this->button.x = x - (button.w / 2);
  this->button.y = y - (button.h / 2);
}

bool Button::IWasClicked(int x, int y){
  return (x > button.x && x < button.x + button.w && y > button.y && y < button.y + button.h);
}

Race* Button::GetRace(){
  return race;
}