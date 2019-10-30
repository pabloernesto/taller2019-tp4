#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Race.h"
#include "../common/CarView.h"
#include "../common/image.h"
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
  void render(SDL_Rect position);
};

#endif    // RACEVIEW_H_
