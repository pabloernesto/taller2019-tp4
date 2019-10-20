#include "RaceView.h"

const int PIXELS_PER_METER = 10;

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector) {
  pixel_vect_s v {
    PIXELS_PER_METER * vector.x,
    PIXELS_PER_METER * vector.y
  };
  return v;
}

void CarView::render() {
  auto p = MKStoPixelTransform(car.GetPosition());
  image.render(renderer);
}

CarView::CarView(SDL_Window *w, SDL_Renderer *r, Car& car)
  : car(car), renderer(r), image("Imagenes/Micro-Machines.bmp", w, r)
{}

void RaceView::render() {}

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race)
  : window(w), renderer(r), race(race), cars()
{}
