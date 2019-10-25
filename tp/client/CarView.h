#ifndef CARVIEW_H_
#define CARVIEW_H_

#include <SDL2/SDL.h>
#include "Race.h"
#include "../common/image.h"
#include <vector>

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
  void reactTo(SDL_Event &event);
};


#endif    // RACEVIEW_H_
