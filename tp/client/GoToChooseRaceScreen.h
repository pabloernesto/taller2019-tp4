#ifndef GOTOCHOOSERACESCREEN_H
#define GOTOCHOOSERACESCREEN_H

#include "Button.h"
#include "Podium.h"

class GoToChooseRaceScreen : public TextButton {
  Podium* context;

public:
  bool OnHandle(void* t) override;

  GoToChooseRaceScreen(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  Podium* context);
};

#endif  // CHOOSERACESCREENBUTTON_H_
