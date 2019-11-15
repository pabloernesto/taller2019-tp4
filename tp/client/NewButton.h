#ifndef NEWBUTTON_H_
#define NEWBUTTON_H_

#include "../common/Responsibility.h"
#include <SDL2/SDL.h>

// A button handles SDL mouse events
class NewButton : public TaskHandler {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Rect click_area;

public:
  virtual void render() = 0;
  
  // Inherited from TaskHandler
  bool ShouldHandle(void* t) override final;
  bool OnHandle(void* t) override = 0;

  NewButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area);
  virtual ~NewButton();
};

#endif  // NEWBUTTON_H_
