#include "NewButton.h"

NewButton::NewButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r)
  : TaskHandler(next), window(w), renderer(r)
{}

NewButton::~NewButton() {}
