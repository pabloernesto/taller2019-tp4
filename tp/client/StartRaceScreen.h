#ifndef STARTRACESCREEN_H_
#define STARTRACESCREEN_H_

#include "GameScreen.h"
#include "Button.h"
#include <memory>   // unique_ptr
#include "RaceProxy.h"

class StartRaceScreen : public GameScreen {
  std::unique_ptr<RaceProxy> race;
  int player_id;
  TTF_Font* font;
  std::unique_ptr<Button> button_chain;
  GameScreen* next_screen;

public:
  GameScreen* start() override;

  StartRaceScreen(SDL_Window *w, SDL_Renderer *r, RaceProxy* race,
    int player_id);
  ~StartRaceScreen();

  friend class StartRaceButton;
};

#endif  // STARTRACESCREEN_H_
