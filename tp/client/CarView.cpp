#include <SDL2/SDL_mixer.h>
#include "CarView.h"
#include "MKStoPixel.h"
#include <math.h>
#include <iostream>
#include "Sound.h"

CarView::CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara)
    ,motor_sound(Sound("Sonidos/Engine noise.wav")),
    break_sound(Sound("Sonidos/skid-piece-fadeinout.wav"))
  {
    motor_sound.SetVolume(8);
    break_sound.SetVolume(50);
  }

CarView::~CarView(){
}

void CarView::render(int tick) {
  std::vector<float> position = this->car.GetPosition();
  std::vector<float> size = this->car.GetSize();

  Image& img = car.isDead() ? imageDead : imageAlive;
  std::vector<Sound*> sounds = {};
  if (car.HasBreakOn()){
    sounds.push_back(&break_sound);
  }
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
