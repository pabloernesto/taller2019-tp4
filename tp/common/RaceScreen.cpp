#include "RaceScreen.h"
#include "Track.h"
#include <vector>
#include "UpdateLoop.h"

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), track("3 3 214060315"), race(track), view(w, r, race)
{}

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  auto& car = race.AddCar();

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      switch(sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
          car.moveLeft();
          break;
        case SDLK_RIGHT:
          car.moveRight();
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
