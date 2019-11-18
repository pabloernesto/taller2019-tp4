#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameScreen.h"
#include "RaceProxy.h"
#include "RaceView.h"

class RaceScreen : public GameScreen {
  std::unique_ptr<RaceProxy> race;
  int carId;
  Mix_Chunk* startEngineSound;
  TTF_Font* font;

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
