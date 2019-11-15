#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include "GameScreen.h"
#include "RaceProxy.h"
#include "RaceView.h"

class RaceScreen : public GameScreen {
  std::unique_ptr<RaceProxy> race;
  int carId;

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
