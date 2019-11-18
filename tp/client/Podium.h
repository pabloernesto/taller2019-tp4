#ifndef PODIUM_H
#define PODIUM_H
#include "GameScreen.h"
#include <string>

class Podium : public GameScreen{
private:
  bool winner;

  void showMessage(std::string message, int size, int x, int y);
public:
  GameScreen* next_screen;
  Podium(SDL_Window *w, SDL_Renderer *r, bool winner);
  GameScreen* start();
};

#endif
