#include "RaceScreen.h"

static const int WIDTH = 600;
static const int HEIGHT = 300;

GameScreen* RaceScreen::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  return nullptr;
}
