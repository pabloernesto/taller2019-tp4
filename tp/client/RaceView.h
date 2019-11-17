#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include "RaceProxy.h"
#include "CarView.h"
#include "TrackView.h"
#include "image.h"
#include "ImageCache.h"
#include "Camara.h"
#include <vector>
#include "CarProxy.h"

// TODO: create View base class

class RaceView {
  RaceProxy* race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView*> cars;
  Camara camara;
  ImageCache imagecache;
  TrackView track;
  CarProxy& car;

public:
  RaceView(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, CarProxy& car);
  ~RaceView();
  void render(int tick);

private:
  void AddCarView(CarProxy& carProxy);
  void renderLife(int life);
  void showMessage(std::string message, int x, int y, int width, int height);
};

#endif    // RACEVIEW_H_
