#include "RaceView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race)
  : window(w), renderer(r), race(race), cars(),
  fondo("Imagenes/pasto.bmp", w, r),
  track(w, r, race.GetTrack()) {}

void RaceView::render(SDL_Rect position, Camara& camara) {
  fondo.render();
  track.render(position);

  auto& base_cars = race.GetCars();

  if (base_cars.size() > cars.size())
    for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
      cars.emplace_back(window, renderer, **it, camara);

  for (auto& car : cars)
    car.render();
}
