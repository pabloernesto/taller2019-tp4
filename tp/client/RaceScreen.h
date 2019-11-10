#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include "GameScreen.h"
#include "../common/Race.h"
#include "RaceView.h"
#include "../common/Track.h"
#include "../common/Posta.h"

class RaceScreen : public GameScreen {
  Race race;

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, std::string race);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
