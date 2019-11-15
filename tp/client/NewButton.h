#ifndef NEWBUTTON_H_
#define NEWBUTTON_H_

#include "../common/Responsibility.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// A button handles SDL mouse events
class NewButton : public TaskHandler {
protected:
  SDL_Rect click_area;

public:
  virtual void render() = 0;
  
  // Inherited from TaskHandler
  bool ShouldHandle(void* t) override final;
  bool OnHandle(void* t) override = 0;

  NewButton(TaskHandler* next, SDL_Rect area);
  virtual ~NewButton();
};

class TextButton : public NewButton {
protected:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::string text;
  TTF_Font* font;
  SDL_Color color;

public:
  void render() override final;

  bool OnHandle(void* t) override = 0;

  TextButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color);
  virtual ~TextButton();
};

#endif  // NEWBUTTON_H_
