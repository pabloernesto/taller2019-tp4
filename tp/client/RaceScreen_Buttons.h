#ifndef RACESCREENBUTTON_H_
#define RACESCREENBUTTON_H_

#include "Button.h"

class RaceScreen;

class StartRaceButton : public TextButton {
  RaceScreen* context;

public:
  bool OnHandle(void* t) override;

  StartRaceButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
    SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
    RaceScreen* context);
};

#endif  // RACESCREENBUTTON_H_
