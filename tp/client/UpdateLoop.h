#ifndef UPDATELOOP_H_
#define UPDATELOOP_H_

#include <SDL2/SDL.h>
#include "../common/Race.h"
#include "RaceView.h"
#include <thread>
#include <atomic>
#include "../common/Camara.h"

class UpdateLoop {
  SDL_Renderer* renderer;
  Race& race;
  RaceView& view;
  std::thread t;

  public:
  UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v);
  std::atomic<bool> quit;
  void Loop();
  void Start();
  void Join();

};

#endif