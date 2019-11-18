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
}

StartRaceScreen::StartRaceScreen(SDL_Window *w, SDL_Renderer *r,
  RaceProxy* race, int player_id)
  : GameScreen(w, r), race(race), player_id(player_id), button_chain(),
  next_screen()
{
  font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);

  // populate button chain
  int x, y;
  SDL_GetWindowSize(window, &x, &y);
  x /= 2;
  y /= 2;

  const int buttonAI_w = 150;
  const int buttonAI_h = 40;
  const SDL_Color colorAI = { 255, 255, 255 };
  SDL_Rect areaAI = {
    x/2 - buttonAI_w/2,   y - buttonAI_h/2,
    buttonAI_w,         buttonAI_h
  };
  StartRaceWithAIButton* startAIButton = 
  new StartRaceWithAIButton(nullptr, w, r, areaAI, "START WITH AI", font, colorAI, this);

  const int buttonNoAI_w = 150;
  const int buttonNoAI_h = 40;
  const SDL_Color colorNoAI = { 255, 255, 255 };
  SDL_Rect areaNoAI = {
    3*x/2 - buttonNoAI_w/2,   y - buttonNoAI_h/2,
    buttonNoAI_w,         buttonNoAI_h
  };
  
  button_chain.reset(
    new StartRaceWithoutAIButton(startAIButton, w, r, areaNoAI, "START WITHOUT AI", font, colorNoAI, this));
}
