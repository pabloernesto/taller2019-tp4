#include "CarView.h"
#include "MKStoPixel.h"
#include <math.h>

CarView::CarView(Image& ailive, Image& dead, CarProxy& car, Camara& camara)
  : car(car), imageAlive(ailive), imageDead(dead), camara(camara) {}

void CarView::render(int tick) {
  std::vector<float> position = this->car.GetPosition();
  std::vector<float> size = this->car.GetSize();

  // The car image points downward, add 180 degrees to flip it up
  Image& img = car.isDead() ? imageDead : imageAlive;
  camara.renderMe(
    position,
    size,
    img,
    M_PI + this->car.GetAngle(),
    tick);
}
