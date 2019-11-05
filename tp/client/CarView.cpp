#include "CarView.h"
#include "../common/MKStoPixel.h"
#include <math.h>

CarView::CarView(Image& ailive, Image& dead, Car& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara) {}

void CarView::render(int tick) {
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
