#ifndef INICIO_H_
#define INICIO_H_
#include <SDL2/SDL.h>
#include <string>

class Inicio{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

public:
  Inicio();
  ~Inicio();

  void start();
};

#endif