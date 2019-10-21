#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include "GameScreen.h"

class RaceScreen : public GameScreen {
public:
  RaceScreen(SDL_Window *&w, SDL_Renderer *&r);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
