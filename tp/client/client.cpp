#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "client.h"
#include "inicio.h"
#include <iostream>
#include "../common/Configuration.h"

extern Configuration configuration;

Client::Client() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096 );
  Mix_AllocateChannels(16);
  window = SDL_CreateWindow(
    (configuration.WINDOW_NAME).c_str(),
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);

  music = Mix_LoadMUS((configuration.SOUNDS_ROUTE + configuration.BACKGROUND_MUSIC).c_str());
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
