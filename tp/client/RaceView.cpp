#include "RaceView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race, Car& car)
  : window(w), renderer(r), race(race), cars(),
  fondo("Imagenes/pasto.bmp", w, r),
  track(w, r, race.GetTrack()),
  camara(0, 0, 600, 400, car),
  imagecache(w, r)
{
  auto& base_cars = race.GetCars();
  for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
    cars.emplace_back(window, renderer, **it, camara);
}

void RaceView::render() {
  camara.Update();
  fondo.render();
  track.render(camara);

  for (auto& car : cars)
    car.render();
}
