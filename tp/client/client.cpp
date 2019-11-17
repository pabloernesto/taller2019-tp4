#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "client.h"
#include "inicio.h"

Client::Client() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 );
  window = SDL_CreateWindow(
    "Micromachines",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    100, 100,
    0);
  renderer = SDL_CreateRenderer(window, -1, 0);
  music = Mix_LoadMUS("Sonidos/Race of the Wasp.wav");
  Mix_PlayMusic( music, -1 );
}

Client::~Client() {
  Mix_FreeMusic(music);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Client::start() {
  screen.reset(new Inicio(window, renderer));
  while (auto new_screen = screen->start())
    screen.reset(new_screen);
}
