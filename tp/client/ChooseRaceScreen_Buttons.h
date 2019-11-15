#ifndef CHOOSERACESCREENBUTTON_H_
#define CHOOSERACESCREENBUTTON_H_

#include "NewButton.h"

class CreateButton : public TextButton {
public:
  bool OnHandle(void* t) override;

  CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color);
};

class JoinButton : public TextButton {
public:
  bool OnHandle(void* t) override;

  JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color);
};

#endif  // CHOOSERACESCREENBUTTON_H_
