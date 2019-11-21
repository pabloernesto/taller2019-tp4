#ifndef RACEVIEW_H_
#define RACEVIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "RaceProxy.h"
#include "CarView.h"
#include "TrackView.h"
#include "image.h"
#include "ImageCache.h"
#include "Camara.h"
#include <vector>
#include "CarProxy.h"
#include "Filmer.h"

// TODO: create View base class

class RaceView {
  RaceProxy* race;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<CarView*> cars;
  Camara camara;
  Filmer filmer;
  ImageCache imagecache;
  TrackView track;
  CarProxy& car;
  TTF_Font* font;

public:
  RaceView(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, CarProxy& car);
  ~RaceView();
  void render(int tick);
  void ChangeFilmingState();

private:
  void AddCarView(CarProxy& carProxy);
  void renderLife(int life);
  void UpdateNewCars();
  void RenderView(int tick);
  void showMessage(std::string message, int x, int y, int width, int height);
};

#endif    // RACEVIEW_H_
