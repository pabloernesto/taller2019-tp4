#include "CarView.h"

const int PIXELS_PER_METER = 100;
// Box2D measures angles counter-clockwise, and SDL does it clockwise
// Shove in a -1 factor to account for that
const float RADIANS_TO_DEGREES_FACTOR = (-1) * 360.0 / (2 * 3.1415);

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector) {
  pixel_vect_s v {
    (int)(PIXELS_PER_METER * vector.x),
    (int)(PIXELS_PER_METER * vector.y)
  };
  return v;
}

CarView::CarView(SDL_Window *w, SDL_Renderer *r, Car& car)
  : car(car), renderer(r), image("Imagenes/pitstop_car_1.bmp", w, r){}

void CarView::render() {
  auto&& size = MKStoPixelTransform(car.GetSize());
  SDL_Rect where = {
    250,    100,   // due to coordinate change, minus-y-coordinate
    size.x, size.y
  };
  auto angle_radians = car.GetAngle();
  // The car image points downward, add 180 degrees to flip it up
  image.render(&where, 180 + angle_radians * RADIANS_TO_DEGREES_FACTOR);
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
