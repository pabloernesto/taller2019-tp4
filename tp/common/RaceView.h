#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include "Race.h"
#include "CarView.h"
#include "image.h"
#include <vector>

// TODO: create View base class

// TODO: move mks to pixel transforms to View base class

class RaceView {
  Race& race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView> cars;
  Image fondo;

public:
  RaceView(SDL_Window *w, SDL_Renderer *r, Race& race);
  void render();
};

#endif    // RACEVIEW_H_
