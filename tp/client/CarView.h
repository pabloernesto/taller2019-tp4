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
  Image& imageAlive;
  Image& imageDead;
  Camara& camara;

public:
  virtual void render(int tick);
  CarView(Image& ailive, Image& dead, Car& car, Camara& camara);
};


#endif    // RACEVIEW_H_
