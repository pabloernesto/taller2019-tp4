#include "FilmButton.h"
#include <SDL2/SDL.h>

#define STARTFILMINGTEXT "Film"
#define STOPFILMINGTEXT "Stop"

FilmButton::FilmButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, TTF_Font* font, SDL_Color color, RaceView* context)
  : TextButton(next, w, r, area, STARTFILMINGTEXT, font, color), context(context)
{}

bool FilmButton::OnHandle(void* t) {
  context->StartFilming();
  text = STOPFILMINGTEXT;
}