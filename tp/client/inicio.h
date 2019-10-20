#ifndef INICIO_H_
#define INICIO_H_

#include "GameScreen.h"

class Inicio : public GameScreen {
public:
  GameScreen* start();
  Inicio(SDL_Window *w, SDL_Renderer *r) : GameScreen(w, r) {}
};

#endif    // INICIO_H_
