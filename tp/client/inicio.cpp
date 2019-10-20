#include "inicio.h"
#include "image.h"

#define WIDTH 640
#define HEIGHT 480
#define FONDO "Imagenes/Micro-Machines.bmp"

GameScreen* Inicio::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  Image fondo(FONDO, this->window, this->renderer);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    fondo.render(this->renderer);
    SDL_RenderPresent(renderer);
  }

  return nullptr;
}
