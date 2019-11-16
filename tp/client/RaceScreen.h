#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameScreen.h"
#include "RaceProxy.h"
#include "RaceView.h"
#include "UpdateLoop.h"

class RaceScreen : public GameScreen {
  std::unique_ptr<RaceProxy> race;
  int carId;
  bool is_Lua;

  Mix_Music* startEngineSound;
  TTF_Font* font;
  
  void userLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop);
  void luaLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop);

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua);
  ~RaceScreen();
  GameScreen* start();

  friend class StartRaceButton;
};

#endif    // RACESCREEN_H_
