#include "CarView.h"
#include "../common/MKStoPixel.h"

CarView::CarView(Image& i, Car& car, Camara& camara)
  : car(car), image(i), camara(camara) {}

void CarView::render() {
  b2Vec2 position = this->car.GetPosition();
  this->camara.renderMe(position, this->car.GetSize(), this->image, this->car.GetAngle());
}
