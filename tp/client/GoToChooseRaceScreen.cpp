#include "GoToChooseRaceScreen.h"
#include "ChooseRaceScreen.h"

GoToChooseRaceScreen::GoToChooseRaceScreen(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  Podium* context)
  : TextButton(next, w, r, area, text, font, color), context(context){}

bool GoToChooseRaceScreen::OnHandle(void* t) {
  context->next_screen = new ChooseRaceScreen(window, renderer);
  return false;
}