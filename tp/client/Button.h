#ifndef BUTTON_H_
#define BUTTON_H_
#include <string>
#include <SDL2/SDL.h>

class Button {
private:
  std::string name;
  SDL_Rect button;
  std::string race;

public:
  Button(std::string name, int width, int height, std::string race);
  ~Button();
  std::string GetName();
  void SetPosition(int x, int y);
  bool IWasClicked(int x, int y);
  std::string GetRace();

};

#endif