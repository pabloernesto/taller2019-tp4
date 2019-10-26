#include "CarView.h"

const int PIXELS_PER_METER = 100;

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
  auto&& p = MKStoPixelTransform(car.GetPosition());
  auto&& size = MKStoPixelTransform(car.GetSize());

  // p is the position of the car's center
  // this correction finds the car's top-left corner
  p.x -= size.x / 2;
  p.y += size.y / 2;

  SDL_Rect where = {
    p.x,    -p.y,   // due to coordinate change, minus-y-coordinate
    size.x, size.y
  };
  image.render(&where, 0);
}

void CarView::reactTo(SDL_Event &event){
  switch( event.key.keysym.sym ){
    case SDLK_LEFT:
        this->car.moveLeft();
        break;
    case SDLK_RIGHT:
        this->car.moveRight();
        break;
    case SDLK_UP:
        this->car.moveUp();
        break;
    case SDLK_DOWN:
        this->car.moveDown();
        break;
    default:
        break;
  }
}