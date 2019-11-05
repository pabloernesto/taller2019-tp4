#include "inicio.h"
#include "../common/image.h"
#include "RaceScreen.h"

#define WIDTH 640
#define HEIGHT 480
#define FONDO "Imagenes/Micro-Machines.bmp"

Inicio::Inicio(SDL_Window* w, SDL_Renderer* r) : GameScreen(w, r) {
}

Inicio::~Inicio(){
}

GameScreen* Inicio::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  Image fondo(FONDO, window, renderer);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN)
      return new RaceScreen(window, renderer);

    fondo.render(0);
    SDL_RenderPresent(renderer);
  }
  return nullptr;
}
