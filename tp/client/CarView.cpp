#include "CarView.h"
#include "../common/MKStoPixel.h"

CarView::CarView(SDL_Window *w, SDL_Renderer *r, Car& car, Camara& camara)
  : car(car), renderer(r), image("Imagenes/pitstop_car_1.bmp", w, r), camara(camara){}

void CarView::render() {
  //b2Vec2 position = {250, 100};
  b2Vec2 position = this->car.GetPosition();
  this->camara.renderMe(position, this->car.GetSize(), this->image, this->car.GetAngle());
}

void CarView::renderAsMain() {
  auto&& size = MKStoPixelTransform(car.GetSize());
  SDL_Rect where = {
    250,    100,   // due to coordinate change, minus-y-coordinate
    size.x, size.y
  };
  auto angle_radians = car.GetAngle();
  // The car image points downward, add 180 degrees to flip it up
  image.render(&where, 180 + angle_radians * RADIANS_TO_DEGREES_FACTOR);
}
