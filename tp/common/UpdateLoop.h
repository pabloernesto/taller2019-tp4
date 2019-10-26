#ifndef UPDATELOOP_H_
#define UPDATELOOP_H_

#include <SDL2/SDL.h>
#include "Race.h"
#include "RaceView.h"
#include <thread>
#include <atomic>

class UpdateLoop {
  SDL_Renderer* renderer;
  Race& race;
  RaceView& view;
  std::thread t;

  void Loop() {
    while (!quit) {
      SDL_RenderClear(renderer);
      race.Step();
      view.render();
      SDL_RenderPresent(renderer);
      SDL_Delay(1000/60);
    }
  }

  public:
  std::atomic<bool> quit;

  void Start() {
    t = std::thread(&UpdateLoop::Loop, this);
  }

  void Join() {
    if (t.joinable()) t.join();
  }

  UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v)
    : renderer(ren), race(r), view(v), t(), quit(false)
  {}
};

#endif