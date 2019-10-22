#include "RaceScreen.h"

static const int WIDTH = 600;
static const int HEIGHT = 300;

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), race(), view(w, r, race)
{}

GameScreen* RaceScreen::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  race.AddCar();

  // TODO: check SDL_QUIT event
  const int limit = 60 * 3;
  for (int i = 0; i < limit; i++) {
    SDL_RenderClear(renderer);
    view.render();
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
  }
  return nullptr;
}
