#include "Button.h"
#include <string>

Button::Button(std::string name, int width, int height, int index, rapidjson::Value&& game)
  : name(name),
  button({0, 0, width * (int) name.size(), height}),
  index(index), game(std::move(game))
{}

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


int Button::GetIndex(){
  return index;
}

int Button::ReactToClick(int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    std::string join = "{\"type\":\"j\",\"id\":" + std::to_string(index) + "}";
    connection.SendStr(join.c_str());
    int id_player;
    {
      char* data = connection.GetStr();
      id_player = atoi(data);
      delete[] data;
    }
    return id_player;
  }
  return -1;
}

rapidjson::Value& Button::GetGame(){
  return game;
}