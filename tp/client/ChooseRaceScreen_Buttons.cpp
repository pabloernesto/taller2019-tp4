#include "ChooseRaceScreen_Buttons.h"
#include <SDL2/SDL.h>

bool CreateButton::OnHandle(void* t) {
  return true;
}

bool JoinButton::OnHandle(void* t) {
  return true;
}



// Constructors/destructors

CreateButton::CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color)
  : TextButton(next, w, r, area, text, font, color)
{}

JoinButton::JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color)
  : TextButton(next, w, r, area, text, font, color)
{}
