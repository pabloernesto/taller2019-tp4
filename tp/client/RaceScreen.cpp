#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include <vector>
#include "UpdateLoop.h"
#include "Camara.h"
#include <iostream>
#include <math.h>
#include "Podium.h"
#include "ChooseRaceScreen.h"

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
  Mix_FreeChunk(startEngineSound);
  TTF_CloseFont(font);
  TTF_Quit();
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId)
  : GameScreen(w, r), race(race), carId(carId), 
  startEngineSound(Mix_LoadWAV("Sonidos/engine_start_up_01.wav")), font()
{
  TTF_Init();
  font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
  Mix_VolumeChunk(startEngineSound, 10);
}

#include <iostream>
GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  Mix_PlayChannel(-1, startEngineSound, 0);

  CarProxy* car = race->GetCar(carId);

  RaceView view(this->window, this->renderer, race.get(), *car);
  UpdateLoop loop(renderer, race.get(), view);
  loop.Start();

  while (!race->Ended()) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerLeft();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerRight();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOn();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOn();
    
    } else if (sdl_event.type == SDL_KEYUP) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOff();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOff();
    }
  }
  std::cout << "va a terminar\n";

  loop.quit = true;
  loop.Join();

  race->Shutdown();
  race->Join();
  std::cout << "termina\n";

  return new ChooseRaceScreen(window, renderer);
}
