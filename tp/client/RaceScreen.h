#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include "GameScreen.h"
#include "Race.h"
#include "RaceView.h"

class RaceScreen : public GameScreen {
  Race race;
  RaceView view;

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
