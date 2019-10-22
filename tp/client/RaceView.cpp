#include "RaceView.h"

const int PIXELS_PER_METER = 10;

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector) {
  pixel_vect_s v {
    (int)(PIXELS_PER_METER * vector.x),
    (int)(PIXELS_PER_METER * vector.y)
  };
  return v;
}

void CarView::render() {
  auto&& p = MKStoPixelTransform(car.GetPosition());
  auto&& size = MKStoPixelTransform(car.GetSize());
  SDL_Rect where = {
    p.x,    p.y,
    size.x, size.y
  };
  image.render(renderer, &where, 0);
}

CarView::CarView(SDL_Window *w, SDL_Renderer *r, Car& car)
  : car(car), renderer(r), image("Imagenes/Micro-Machines.bmp", w, r)
{}

void RaceView::render() {
  auto& base_cars = race.GetCars();

  if (base_cars.size() > cars.size())
    for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
      cars.emplace_back(window, renderer, *it);

  for (auto& car : cars)
    car.render();
}

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race)
  : window(w), renderer(r), race(race), cars()
{}
