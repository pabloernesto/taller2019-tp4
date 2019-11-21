#include "inicio.h"
#include "image.h"
#include "ChooseRaceScreen.h"

#define FONDO "Imagenes/Micro-Machines.bmp"

Inicio::Inicio(SDL_Window* w, SDL_Renderer* r) : GameScreen(w, r) {
}

Inicio::~Inicio(){
}

GameScreen* Inicio::start() {
  Image fondo(FONDO, window, renderer);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN)
      return new ChooseRaceScreen(window, renderer);

    fondo.render(0);
    SDL_RenderPresent(renderer);
  }
  return nullptr;
}
