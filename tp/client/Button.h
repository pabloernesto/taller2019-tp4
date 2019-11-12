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
  RaceProxy* race;

public:
  Button(std::string name, int width, int height, RaceProxy* race);
  ~Button();
  std::string GetName();
  void SetPosition(int x, int y);
  bool IWasClicked(int x, int y);
  RaceProxy* GetRace();

};

#endif