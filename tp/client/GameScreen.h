#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <SDL2/SDL.h>

class GameScreen {
protected:
  SDL_Window* window;
  SDL_Renderer* renderer;

public:
  // Derived classes should do their work in this method
  // Return a pointer to the next screen, if any
  virtual GameScreen* start() = 0;

  GameScreen(SDL_Window* w, SDL_Renderer* r) : window(w), renderer(r) {}
  virtual ~GameScreen() = default;
};

#endif    // GAMESCREEN_H_
