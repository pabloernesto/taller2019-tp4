#include <SDL2/SDL_mixer.h>
#include "CarView.h"
#include "MKStoPixel.h"
#include <math.h>
#include <iostream>

CarView::CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara),
    motor_sound(Mix_LoadWAV("Sonidos/engine noise 2.wav")),
    break_sound(Mix_LoadWAV("Sonidos/skid-piece-fadeinout.wav"))
  {
    Mix_VolumeChunk(motor_sound, 10);
    Mix_VolumeChunk(break_sound, 20);
  }

CarView::~CarView(){
  Mix_FreeChunk(break_sound);
  Mix_FreeChunk(motor_sound);
}

void CarView::render(int tick) {
  std::vector<float> position = this->car.GetPosition();
  std::vector<float> size = this->car.GetSize();

  // The car image points downward, add 180 degrees to flip it up
  Image& img = car.isDead() ? imageDead : imageAlive;
  std::vector<Mix_Chunk*> sounds = {motor_sound};
  if (car.HasBreakOn()){
    sounds.push_back(break_sound);
  }
  camara.renderMe(
    position,
    size,
    img,
    sounds,
    M_PI + this->car.GetAngle(),
    tick);
}
