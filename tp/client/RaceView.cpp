#include "RaceView.h"

RaceView::RaceView(SDL_Window *w, SDL_Renderer *r, Race& race, Car& car)
  : window(w), renderer(r), race(race), cars(),
  camara(0, 0, 600, 400, car),
  imagecache(w, r),
  track(imagecache, race.GetTrack())
{
  imagecache.LoadAnimation("Imagenes/pitstop_car_1.png", 3, 1, 10);
  auto& base_cars = race.GetCars();
  for (auto it = base_cars.begin() + cars.size(); it != base_cars.end(); it++)
    cars.emplace_back(
      imagecache.getImage("Imagenes/pitstop_car_1.png"),
      imagecache.getImage("Imagenes/explosion.bmp"),
      **it, camara);
}

void RaceView::render(int tick) {
  camara.Update();
  SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
  track.render(camara, this->race.getTrackPieces());

  for (auto& car : cars)
    car.render(tick);
}
