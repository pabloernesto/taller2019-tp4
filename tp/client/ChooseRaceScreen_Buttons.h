#ifndef CHOOSERACESCREENBUTTON_H_
#define CHOOSERACESCREENBUTTON_H_

#include "Button.h"

class ChooseRaceScreen;

class RaceButton : public TextButton {
  ChooseRaceScreen* context;
  std::string msg;

public:
  bool OnHandle(void* t) override;

  RaceButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color,
    ChooseRaceScreen* context, std::string msg);
};

class CreateButton : public RaceButton {
public:
  CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color,
    ChooseRaceScreen* context);
};

class JoinButton : public RaceButton {
public:
  JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r, SDL_Rect area,
    std::string text, TTF_Font* font, SDL_Color color,
    int id_game, ChooseRaceScreen* context);
};

#endif  // CHOOSERACESCREENBUTTON_H_
