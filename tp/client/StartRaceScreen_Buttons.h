#ifndef STARTRACEBUTTON_H_
#define STARTRACEBUTTON_H_

#include "Button.h"

class StartRaceScreen;

class StartRaceWithoutAIButton : public TextButton {
  StartRaceScreen* context;

public:
  bool OnHandle(void* t) override;

  StartRaceWithoutAIButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
    SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
    StartRaceScreen* context);
};

class StartRaceWithAIButton : public TextButton {
  StartRaceScreen* context;

public:
  bool OnHandle(void* t) override;

  StartRaceWithAIButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
    SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
    StartRaceScreen* context);
};

#endif  // STARTRACEBUTTON_H_
