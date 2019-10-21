#ifndef INICIO_H_
#define INICIO_H_

#include "GameScreen.h"

class Inicio : public GameScreen {
public:
  Inicio(SDL_Window* &w, SDL_Renderer* &r);
  ~Inicio();
  GameScreen* start();
};

#endif    // INICIO_H_
