#include "RaceScreen.h"
#include "Track.h"
#include <vector>
#include "UpdateLoop.h"
#include "Camara.h"

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), race("3 3 204161305"), view(w, r, race)
{}

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  //auto& car = race.AddMainCar();
  auto&& car = race.AddCar();
  Camara camara = Camara(0, 0, 600, 400, car);

  UpdateLoop loop(renderer, race, view, camara);
  loop.Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      switch(sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
          car.SteerLeft();
          break;
        case SDLK_RIGHT:
          car.SteerRight();
          break;
        case SDLK_UP:
          car.GasOn();
          break;
        case SDLK_DOWN:
          car.BreakOn();
          break;
        default:
          break;
      }
    }
    if (sdl_event.type == SDL_KEYUP) {
      switch(sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
          car.SteerCenter();
          break;
        case SDLK_RIGHT:
          car.SteerCenter();
          break;
        case SDLK_UP:
          car.GasOff();
          break;
        case SDLK_DOWN:
          car.BreakOff();
          break;
      default:
        break;
      }
    }
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}
