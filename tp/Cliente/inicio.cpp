#include "inicio.h"
#include "image.h"

#define WIDTH 480
#define HEIGHT 640
#define FONDO "Imagenes/Micro-Machines.bmp"

Inicio::Inicio(): window(SDL_CreateWindow("Micromachines",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    HEIGHT, WIDTH, 0)),
    renderer(SDL_CreateRenderer(window, -1, 0)){

}

Inicio::~Inicio(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Inicio::start(){
  Image fondo(FONDO, this->window, this->renderer);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    fondo.render(this->renderer);
    SDL_RenderPresent(renderer);
  }

}