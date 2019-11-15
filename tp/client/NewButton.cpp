#include "NewButton.h"

bool NewButton::ShouldHandle(void* t) {
  SDL_Event* e = (SDL_Event*) t;
  SDL_Point click_pos{ e->button.x, e->button.y };
  return
    e->button.button == SDL_BUTTON_LEFT
    && SDL_PointInRect(&click_pos, &click_area);
}


NewButton::~NewButton() {}

NewButton::NewButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area)
  : TaskHandler(next), window(w), renderer(r), click_area(area)
{}
