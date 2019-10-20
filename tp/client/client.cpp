#include <SDL2/SDL.h>
#include "client.h"
#include "inicio.h"

Client::Client() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow(
    "Micromachines",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    100, 100,
    0);
  renderer = SDL_CreateRenderer(window, -1, 0);
}

Client::~Client() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Client::start() {
  screen.reset(new Inicio(window, renderer));
  while (auto new_screen = screen->start())
    screen.reset(new_screen);
}
