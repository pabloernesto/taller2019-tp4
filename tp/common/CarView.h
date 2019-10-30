#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include "Car.h"
#include "../common/Race.h"
#include "../common/image.h"
#include <vector>

class CarView {
  Car& car;
  SDL_Renderer *renderer;
  Image image;

public:
  virtual void render();
  virtual void renderAsMain();
  CarView(SDL_Window *w, SDL_Renderer *r, Car& car);
};


#endif    // RACEVIEW_H_
