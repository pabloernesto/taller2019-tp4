#include "RaceView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race)
  : window(w), renderer(r), race(race), cars(),
  fondo("Imagenes/pasto.bmp", w, r) {}

void RaceView::render() {
  fondo.render();
  race.GetTrack().render(window,renderer);

  auto& base_cars = race.GetCars();

  if (base_cars.size() > cars.size())
    for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
      cars.emplace_back(window, renderer, **it);

  for (auto& car : cars)
    car.render();
}
