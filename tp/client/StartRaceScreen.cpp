#include "StartRaceScreen.h"
#include "StartRaceScreen_Buttons.h"

GameScreen* StartRaceScreen::start() {
  while (!next_screen) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    // NOTE: Handle() may alter next_screen
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
      button_chain->Handle(&sdl_event);
    
    SDL_RenderClear(renderer);
    button_chain->render();
    SDL_RenderPresent(renderer);
  }
  return next_screen;
}

StartRaceScreen::~StartRaceScreen() {
  TTF_CloseFont(font);
  TTF_Quit();
}

StartRaceScreen::StartRaceScreen(SDL_Window *w, SDL_Renderer *r,
  RaceProxy* race, int player_id)
  : GameScreen(w, r), race(race), player_id(player_id), button_chain(),
  next_screen()
{
  TTF_Init();
  font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);

  // populate button chain
  int x, y;
  SDL_GetWindowSize(window, &x, &y);
  x /= 2;
  y /= 70;

  const int button_w = 150;
  const int button_h = 40;
  const SDL_Color color = { 255, 255, 255 };
  SDL_Rect area = {
    x - button_w/2,   y + button_h/2,
    button_w,         button_h
  };
  button_chain.reset(
    new StartRaceButton(nullptr, w, r, area, "START", font, color, this));
}
