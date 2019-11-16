#ifndef CHOOSERACESCREENBUTTON_H_
#define CHOOSERACESCREENBUTTON_H_

#include "Button.h"

class ChooseRaceScreen;

class CreateButton : public TextButton {
  ChooseRaceScreen* context;

public:
  bool OnHandle(void* t) override;

  CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color,
    ChooseRaceScreen* context);
};

class JoinButton : public TextButton {
  int id_game;
  ChooseRaceScreen* context;

public:
  bool OnHandle(void* t) override;

  JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color,
    int id_game, ChooseRaceScreen* context);
};

#endif  // CHOOSERACESCREENBUTTON_H_
