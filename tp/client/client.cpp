#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "client.h"
#include "inicio.h"
#include <iostream>

Client::Client() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 );
  window = SDL_CreateWindow(
    "Micromachines",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    100, 100,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, 0);

  music = Mix_LoadMUS("Sonidos/Race of the Wasp.wav");
  if (music) Mix_PlayMusic( music, -1 );
  else std::cerr << "Client: failed to load background music\n";

  TTF_Init();
}

Client::~Client() {
  TTF_Quit();
  Mix_FreeMusic(music);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Client::start() {
  screen.reset(new Inicio(window, renderer));
  try {
    while (auto new_screen = screen->start())
      screen.reset(new_screen);
  } catch (std::runtime_error& e){
    SDL_ShowSimpleMessageBox(0, "Error", e.what(), window);
  }
}
