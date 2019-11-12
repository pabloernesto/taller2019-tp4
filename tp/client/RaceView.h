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
#include "CarProxy.h"

// TODO: create View base class

// TODO: move mks to pixel transforms to View base class

class RaceView {
  std::unique_ptr<Race>& race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView> cars;
  Camara camara;
  ImageCache imagecache;
  TrackView track;
  CarProxy& car;

public:
  RaceView(SDL_Window *w, SDL_Renderer *r, std::unique_ptr<Race>& race, CarProxy& car);
  ~RaceView();
  void render(int tick);

private:
  void showMessage(std::string message);
};

#endif    // RACEVIEW_H_
