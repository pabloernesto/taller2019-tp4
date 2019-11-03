#include "RaceView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race, Car& car)
  : window(w), renderer(r), race(race), cars(),
  track(w, r, race.GetTrack()),
  camara(0, 0, 600, 400, car),
  imagecache(w, r)
{
  auto& base_cars = race.GetCars();
  for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
    cars.emplace_back(
      imagecache.getImage("Imagenes/pitstop_car_1.bmp"), **it, camara);
}

void RaceView::render() {
  camara.Update();
  SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
  track.render(camara, this->race.getTrackPieces());

  for (auto& car : cars)
    car.render();
}
