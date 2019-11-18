#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include <vector>
#include "Camara.h"
#include <iostream>
#include <math.h>
#include "Podium.h"
#include <dlfcn.h>
#include "Ai.h"
#include "StartRaceScreen_Buttons.h"

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
  Mix_FreeChunk(startEngineSound);
  TTF_CloseFont(font);
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua)
  : GameScreen(w, r), race(race), carId(carId), is_Lua(is_Lua),
  startEngineSound(Mix_LoadWAV("Sonidos/engine_start_up_01.wav")), font()
{
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

  if (is_Lua){
    luaLoop(sdl_event, car, loop);
  } else {
    userLoop(sdl_event, car, loop);
  }

  loop.quit = true;
  loop.Join();

  race->Shutdown();
  race->Join();

  if (race->Ended())
    return new Podium(window, renderer, (race->GetWinnerId() == car->GetId()));
  return nullptr;
}

void RaceScreen::luaLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop){

  // void *shared_lib = dlopen("./lua/Ai.so", RTLD_NOW);
  // char* err = dlerror();
  // if (!shared_lib){
    // throw std::runtime_error(std::string(err));
  // }
  
  // Ai* (*create)(CarProxy*, RaceProxy*);
  // void (*destroy)(Ai*);
  // create = (Ai* (*)(CarProxy*, RaceProxy*))dlsym(shared_lib, "createAi");
  // destroy = (void (*)(Ai*))dlsym(shared_lib, "destroyAi");
  
  Ai ai(car, this->race.get());
  ai.Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);
    if (sdl_event.type == SDL_QUIT) break;
  }
  
  ai.Shutdown();
  ai.Join();

  // destroy(ai);   
  // dlclose(shared_lib);
}

void RaceScreen::userLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop){
  while (true) {
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
}