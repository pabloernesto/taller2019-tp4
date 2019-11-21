#ifndef RACESCREEN_H_
#define RACESCREEN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameScreen.h"
#include "RaceProxy.h"
#include "RaceView.h"
#include "UpdateLoop.h"
#include "Sound.h"

class RaceScreen : public GameScreen {
  std::unique_ptr<RaceProxy> race;
  int carId;
  bool is_Lua;
  Sound startEngineSound;
  
  void userLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop, RaceView& view);
  void luaLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop, RaceView& view);

public:
  RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua);
  ~RaceScreen();
  GameScreen* start();
};

#endif    // RACESCREEN_H_
