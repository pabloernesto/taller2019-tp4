#include <SDL2/SDL_mixer.h>
#include "CarView.h"
#include "MKStoPixel.h"
#include <math.h>
#include <iostream>
#include "Sound.h"
#include "../common/Configuration.h"

#define ENGINENOISE "Engine noise.wav"
#define BREAKNOISE "skid-piece-fadeinout.wav"
#define CRASHNOISE "crash_sound.wav"

extern Configuration configuration;

CarView::CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara),
  motor_sound(Sound(configuration.SOUNDS_ROUTE + ENGINENOISE)),
  break_sound(Sound(configuration.SOUNDS_ROUTE + BREAKNOISE)),
  crash_sound(configuration.SOUNDS_ROUTE + CRASHNOISE)
{
  motor_sound.SetVolume(8);
  break_sound.SetVolume(50);
  crash_sound.SetVolume(70);
}

CarView::~CarView(){
}

void CarView::render(int tick) {
  std::vector<float> position = this->car.GetPosition();
  std::vector<float> size = this->car.GetSize();

  Image& img = car.isDead() ? imageDead : imageAlive;
  std::vector<Sound*> sounds = {};
  if (car.HasBreakOn()) sounds.push_back(&break_sound);
  if (car.WasContactedLastTick()) sounds.push_back(&crash_sound);
  sounds.push_back(&motor_sound);
  
  // The car image points downward, add 180 degrees to flip it up
  camara.renderMe(
    position,
    size,
    img,
    sounds,
    M_PI + this->car.GetAngle(),
    tick);
}
