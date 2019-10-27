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
  race.AddCar();

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  // TODO: check SDL_QUIT event
  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    view.reactTo(sdl_event);
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}
