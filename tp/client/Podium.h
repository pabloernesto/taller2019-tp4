#ifndef PODIUM_H
#define PODIUM_H
#include "GameScreen.h"
#include <string>

class Podium : public GameScreen{
private:
  bool winner;

  void showMessage(std::string message, int x, int y, int width, int height);
public:
  Podium(SDL_Window *w, SDL_Renderer *r, bool winner);
  GameScreen* start();
};

#endif
