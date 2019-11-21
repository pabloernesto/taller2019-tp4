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

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua)
  : GameScreen(w, r), race(race), carId(carId), is_Lua(is_Lua),
  startEngineSound(Sound("Sonidos/engine_start_up_01.wav"))
{
  startEngineSound.SetVolume(10);
}

#include <iostream>
GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  startEngineSound.Play();

  CarProxy* car = race->GetCar(carId);

  RaceView view(this->window, this->renderer, race.get(), *car);
  UpdateLoop loop(renderer, race.get(), view);
  loop.Start();

  if (is_Lua){
    luaLoop(sdl_event, car, loop, view);
  } else {
    userLoop(sdl_event, car, loop, view);
  }

  loop.quit = true;
  loop.Join();

  race->Shutdown();
  race->Join();

  if (race->Ended() && race->GetWinnerId() != -1)
    return new Podium(window, renderer, (race->GetWinnerId() == car->GetId()));
  return nullptr;
}

void RaceScreen::luaLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop, RaceView& view){

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

  bool error_shown = false;
  while (race->GetWinnerId() == -1) {
    SDL_WaitEvent(&sdl_event);
    if (sdl_event.type == SDL_QUIT) break;
    if (!error_shown && race->Ended() && race->GetWinnerId() == -1){
      SDL_ShowSimpleMessageBox(0, "Error", "exception", window);
      error_shown = true;
    }
    if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_f) {
      view.ChangeFilmingState();
    }
  }
  
  ai.Shutdown();
  ai.Join();

  // destroy(ai);   
  // dlclose(shared_lib);
}

void RaceScreen::userLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop, RaceView& view){
  bool ignoring_keyboard = false;
  while (race->GetWinnerId() == -1) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    try {
      if (ignoring_keyboard) {
        ; // pass
      } else if (sdl_event.type == SDL_KEYDOWN) {
        if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerLeft();
        else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerRight();
        else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOn();
        else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOn();
        else if (sdl_event.key.keysym.sym == SDLK_f) view.ChangeFilmingState();
      
      } else if (sdl_event.type == SDL_KEYUP) {
        if (sdl_event.key.keysym.sym == SDLK_LEFT) car->SteerCenter();
        else if (sdl_event.key.keysym.sym == SDLK_RIGHT) car->SteerCenter();
        else if (sdl_event.key.keysym.sym == SDLK_UP) car->GasOff();
        else if (sdl_event.key.keysym.sym == SDLK_DOWN) car->BreakOff();
      }
    } catch (std::runtime_error& e) {
      // msg
      SDL_ShowSimpleMessageBox(0, "Error", e.what(), window);
      ignoring_keyboard = true;
      race->Shutdown();
    }
  }
}