#include "RaceScreen.h"
#include "../common/Track.h"
#include <vector>
#include "UpdateLoop.h"
#include "../common/Camara.h"
#include <iostream>
#include <math.h>

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, Race* race)
  : GameScreen(w, r), race(race)
{}

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  race->AddCar(0,-20, 1); //para probar que puede mostrar varios autos a la vez
  race->AddCar(3,-20, 2); //para probar que puede mostrar varios autos a la vez
  RaceView view(this->window, this->renderer, race, race->AddCar(7,-20, 3));
  //auto&& car = *(race.GetCars()[0]);
  auto&& car = *(race->GetCars()[2]);

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car.SteerLeft();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car.SteerRight();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car.GasOn();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car.BreakOn();
    }
    if (sdl_event.type == SDL_KEYUP) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car.SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car.SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car.GasOff();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car.BreakOff();
    }
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}
