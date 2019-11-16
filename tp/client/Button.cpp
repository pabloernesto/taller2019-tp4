#include "Button.h"

bool Button::ShouldHandle(void* t) {
  SDL_Event* e = (SDL_Event*) t;
  SDL_Point click_pos{ e->button.x, e->button.y };
  return
    e->button.button == SDL_BUTTON_LEFT
    && SDL_PointInRect(&click_pos, &click_area);
}

void TextButton::render() {
  if (next) ((Button*) next.get())->render();

  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_RenderCopy(renderer, texture, NULL, &click_area);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}



// Constructors/destructors

Button::~Button() {}

Button::Button(TaskHandler* next, SDL_Rect area)
  : TaskHandler(next), click_area(area)
{}

TextButton::TextButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color)
  : Button(next, area), window(w), renderer(r), text(text), font(font),
  color(color)
{}

TextButton::~TextButton() {}
