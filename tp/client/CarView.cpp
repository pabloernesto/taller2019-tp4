#include "CarView.h"
#include "../common/MKStoPixel.h"
#include <math.h>

CarView::CarView(Image& ailive, Image& dead, Car& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara) {}

void CarView::render(int tick) {
  RenderSmoke(tick);
  b2Vec2 position = this->car.GetPosition();

  // The car image points downward, add 180 degrees to flip it up
  Image& img = car.isDead() ? imageDead : imageAlive;
  camara.renderMe(
    position,
    this->car.GetSize(),
    img,
    M_PI + this->car.GetAngle(),
    tick);
}

void CarView::RenderSmoke(int tick) {
  // Where is the car's back end?
  b2Vec2 facing(0, 1);
  b2Rot rot(car.GetAngle());
  facing = b2Mul(rot, facing);
  auto position = car.GetPosition();
  auto backend = position - car.GetSize().y * facing;

  // TODO: Tie animation framerate to car life
  
  camara.renderMe(backend, car.GetSize(), imageDead, M_PI + car.GetAngle(), tick);
}
