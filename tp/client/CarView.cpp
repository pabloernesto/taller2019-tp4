#include "CarView.h"
#include "../common/MKStoPixel.h"
#include <math.h>

CarView::CarView(Image& i, Car& car, Camara& camara)
  : car(car), image(i), camara(camara) {}

void CarView::render() {
  b2Vec2 position = this->car.GetPosition();

  // The car image points downward, add 180 degrees to flip it up
  this->camara.renderMe(position, this->car.GetSize(), this->image, M_PI + this->car.GetAngle());
}
