#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include "CarProxy.h"
#include "image.h"
#include "Camara.h"
#include <vector>

class CarView {
  CarProxy& car;
  Image& imageAlive;
  Image& imageDead;
  Camara& camara;

public:
  virtual void render(int tick);
  CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara);
};


#endif    // RACEVIEW_H_
