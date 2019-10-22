#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Race.h"
#include "../common/image.h"
#include <vector>

// TODO: create View base class

// TODO: move mks to pixel transforms to View base class
typedef struct {
  int x;
  int y;
} pixel_vect_s;

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector);

class CarView {
  Car& car;
  SDL_Renderer *renderer;
  Image image;

public:
  void render();
  CarView(SDL_Window *w, SDL_Renderer *r, Car& car);
};

class RaceView {
  Race& race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView> cars;
  Image fondo;

public:
  void render();
  RaceView(SDL_Window *w, SDL_Renderer *r, Race& race);
};

#endif    // RACEVIEW_H_
