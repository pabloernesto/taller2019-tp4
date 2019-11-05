#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Race.h"
#include "CarView.h"
#include "TrackView.h"
#include "../common/image.h"
#include "../common/ImageCache.h"
#include "../common/Camara.h"
#include <vector>

// TODO: create View base class

// TODO: move mks to pixel transforms to View base class

class RaceView {
  Race& race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView> cars;
  Camara camara;
  ImageCache imagecache;
  TrackView track;

public:
  RaceView(SDL_Window *w, SDL_Renderer *r, Race& race, Car& car);
  void render(int tick);
};

#endif    // RACEVIEW_H_
