#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Car.h"
#include "../common/Race.h"
#include "../common/image.h"
#include "../common/Camara.h"
#include <vector>

class CarView {
  Car& car;
  SDL_Renderer *renderer;
  Image image;
  Camara& camara;

public:
  virtual void render();
  CarView(SDL_Window *w, SDL_Renderer *r, Car& car, Camara& camara);
};


#endif    // RACEVIEW_H_
