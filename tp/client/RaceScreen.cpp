#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include <vector>
#include "Camara.h"
#include <iostream>
#include <math.h>
#include <dlfcn.h>
#include "lua/Ai.h"
#include "RaceScreen_Buttons.h"

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
  Mix_FreeMusic(startEngineSound);
  TTF_CloseFont(font);
  TTF_Quit();
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race, int carId, bool is_Lua)
  : GameScreen(w, r), race(race), carId(carId), is_Lua(is_Lua),
  startEngineSound(Mix_LoadMUS("Sonidos/engine_start_up_01.wav")), font()
{
  TTF_Init();
  font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
}

#include <iostream>
GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  Mix_PlayMusic( startEngineSound, -1 );

  std::cerr << "RaceScreen::start id " << carId << "\n";
  CarProxy* car = race->GetCar(carId);

  RaceView view(this->window, this->renderer, race.get(), *car);
  UpdateLoop loop(renderer, race.get(), view);
  // Add start button to loop
  // TODO: destroy buttons once they are used
  {
    SDL_Point screen_center = { WIDTH/2, HEIGHT/2 };
    SDL_Rect area = {
      screen_center.x - 100/2,  screen_center.y + 40/2,
      100,                      40
    };
    SDL_Color color = { 255, 255, 255 };
    loop.button_chain.reset(new StartRaceButton(
      nullptr, window, renderer, area, "START", font, color, this));
  }
  loop.Start();

  if (is_Lua){
    luaLoop(sdl_event, car, loop);
  } else {
    userLoop(sdl_event, car, loop);
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}


void RaceScreen::luaLoop(SDL_Event& sdl_event, CarProxy* car, UpdateLoop& loop){

  void *shared_lib = dlopen("./lua/Ai.so", RTLD_NOW);
  char* err = dlerror();
  if (!shared_lib){
    throw std::runtime_error(std::string(err));
  }
  
  Ai* (*create)(CarProxy*, RaceProxy*);
  void (*destroy)(Ai*);
  create = (Ai* (*)(CarProxy*, RaceProxy*))dlsym(shared_lib, "createAi");
  destroy = (void (*)(Ai*))dlsym(shared_lib, "destroyAi");
  
  Ai* ai = (Ai*)create(car, this->race.get());
  ai->Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);
    if (sdl_event.type == SDL_QUIT) break;
    
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN) {
      if (loop.button_chain) loop.button_chain->Handle(&sdl_event);
    }

  }
  
  ai->Shutdown();
  ai->Join();

  destroy(ai);   
  dlclose(shared_lib);
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
    
    } else if (sdl_event.type == SDL_MOUSEBUTTONDOWN) {
      if (loop.button_chain) loop.button_chain->Handle(&sdl_event);
    }
  }
}