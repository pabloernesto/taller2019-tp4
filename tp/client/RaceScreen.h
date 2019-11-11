#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include "GameScreen.h"
#include "../common/Race.h"
#include "RaceView.h"
#include "../common/Track.h"
#include "../common/Posta.h"

class RaceScreen : public GameScreen {
  std::unique_ptr<Race> race;

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, Race* race);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
