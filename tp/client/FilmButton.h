#ifndef FILMBUTTON_H
#define FILMBUTTON_H

#include "Button.h"
#include "RaceView.h"

class FilmButton : public TextButton {
  RaceView* context;

public:
  bool OnHandle(void* t) override;

  FilmButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, TTF_Font* font, SDL_Color color, RaceView* context);
};

#endif  // CHOOSERACESCREENBUTTON_H_
