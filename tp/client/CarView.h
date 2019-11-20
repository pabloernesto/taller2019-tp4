#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "CarProxy.h"
#include "image.h"
#include "Camara.h"
#include <vector>
#include "Sound.h"

class CarView {
  CarProxy& car;
  Image& imageAlive;
  Image& imageDead;
  Camara& camara;
  Sound motor_sound;
  Sound break_sound;

public:
  CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara);
  ~CarView();
  virtual void render(int tick);
};


#endif    // RACEVIEW_H_
