#include "StartRaceScreen.h"

GameScreen* StartRaceScreen::start() {
  while (!next_screen) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    // NOTE: Handle() may alter next_screen
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
      button_chain->Handle(&sdl_event);
  }
  return next_screen;
}

StartRaceScreen::~StartRaceScreen() {}

StartRaceScreen::StartRaceScreen(SDL_Window *w, SDL_Renderer *r,
  RaceProxy* race)
  : GameScreen(w, r), race(race), button_chain(), next_screen()
{
  // TODO: populate button chain
}
