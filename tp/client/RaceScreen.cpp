#include "RaceScreen.h"
#include <vector>
#include "UpdateLoop.h"
#include "Camara.h"
#include <iostream>
#include <math.h>
#include "lua/Ai.h"
#include <dlfcn.h>

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua)
  : GameScreen(w, r), race(race), carId(carId), is_Lua(is_Lua)
{}

#include <iostream>
GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  std::cerr << "RaceScreen::start id " << carId << "\n";
  CarProxy* car = race->GetCar(carId);
  RaceView view(this->window, this->renderer, race.get(), *car);
  UpdateLoop loop(renderer, race.get(), view);
  loop.Start();

  if (is_Lua){
    luaLoop(sdl_event, car);
  } else {
    userLoop(sdl_event, car);
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}


void RaceScreen::luaLoop(SDL_Event& sdl_event, CarProxy* car){

  void *shared_lib = dlopen("./07_lib.so", RTLD_NOW);
  char* err = dlerror();
  if (!shared_lib){
    // levantar excepcion;
  }
  
  Ai* (*create)(CarProxy*);
  void (*destroy)(Ai*);
  create = (Ai* (*)(CarProxy*))dlsym(shared_lib, "createAi");
  destroy = (void (*)(Ai*))dlsym(shared_lib, "destroyAi");
  
  Ai* ai = (Ai*)create(car);
  ai->Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);
    if (sdl_event.type == SDL_QUIT) break;
  }
  
  ai->Shutdown();
  ai->Join();

  destroy(ai);   
  dlclose(shared_lib);
}

void RaceScreen::userLoop(SDL_Event& sdl_event, CarProxy* car){
  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerLeft();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerRight();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOn();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOn();
    }
    if (sdl_event.type == SDL_KEYUP) {
      if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerCenter();
      else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOff();
      else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOff();
    }
  }
}