#include "CarView.h"
#include "../common/MKStoPixel.h"

CarView::CarView(SDL_Window *w, SDL_Renderer *r, Car& car, Camara& camara)
  : car(car), renderer(r), image("Imagenes/pitstop_car_1.bmp", w, r), camara(camara){}

void CarView::render() {
  b2Vec2 position = this->car.GetPosition();
  this->camara.renderMe(position, this->car.GetSize(), this->image, this->car.GetAngle());
}
