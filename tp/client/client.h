#ifndef CLIENT_H_
#define CLIENT_H_

#include <SDL2/SDL.h>
#include <memory>   // unique_ptr
#include "../common/GameScreen.h"

class Client {
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::unique_ptr<GameScreen> screen;

public:
  Client();
  ~Client();

  void start();
};

#endif