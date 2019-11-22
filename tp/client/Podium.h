#ifndef PODIUM_H
#define PODIUM_H
#include "GameScreen.h"
#include <string>
#include <SDL2/SDL_ttf.h>

class Podium : public GameScreen{
private:
  bool winner;
  TTF_Font* font;

  void showMessage(std::string message, int size, int x, int y);
public:
  GameScreen* next_screen;
  Podium(SDL_Window *w, SDL_Renderer *r, bool winner);
  ~Podium();
  GameScreen* start();
};

#endif
