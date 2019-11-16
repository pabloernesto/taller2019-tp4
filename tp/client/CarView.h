#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "CarProxy.h"
#include "image.h"
#include "Camara.h"
#include <vector>

class CarView {
  CarProxy& car;
  Image& imageAlive;
  Image& imageDead;
  Camara& camara;
  Mix_Chunk* motor_sound;
  Mix_Chunk* break_sound;

public:
  CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara);
  ~CarView();
  virtual void render(int tick);
};


#endif    // RACEVIEW_H_
