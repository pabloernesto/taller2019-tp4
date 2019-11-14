#ifndef BUTTON_H_
#define BUTTON_H_
#include <string>
#include <SDL2/SDL.h>
#include <memory>   // unique_ptr
#include "RaceProxy.h"

class Button {
private:
  std::string name;
  SDL_Rect button;
  int index;
  rapidjson::Value game;

public:
  Button(std::string name, int width, int height, int index, rapidjson::Value&& game);
  ~Button();
  std::string GetName();
  void SetPosition(int x, int y);
  bool IWasClicked(int x, int y);
  int GetIndex();
  int ReactToClick(int x, int y, Connection& connection);
  rapidjson::Value& GetGame();
};

#endif