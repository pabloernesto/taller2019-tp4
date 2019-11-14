#ifndef UPDATELOOP_H_
#define UPDATELOOP_H_

#include <SDL2/SDL.h>
#include "RaceProxy.h"
#include "RaceView.h"
#include <thread>
#include <atomic>
#include "Camara.h"

class UpdateLoop {
  SDL_Renderer* renderer;
  RaceProxy* race;
  RaceView& view;
  std::thread t;

  public:
  UpdateLoop(SDL_Renderer* ren, RaceProxy* r, RaceView& v);
  std::atomic<bool> quit;
  void Loop();
  void Start();
  void Join();

};

#endif