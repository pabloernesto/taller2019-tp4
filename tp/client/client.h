#ifndef CLIENT_H_
#define CLIENT_H_

#include <SDL2/SDL.h>
#include <memory>   // unique_ptr
#include "GameScreen.h"
#include <SDL2/SDL_mixer.h>

class Client {
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::unique_ptr<GameScreen> screen;
  Mix_Music* music;

public:
  Client();
  ~Client();

  void start();
};

#endif