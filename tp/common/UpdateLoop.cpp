#include "UpdateLoop.h"


UpdateLoop::UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v)
  : renderer(ren), race(r), view(v), t(), quit(false)
{}

void UpdateLoop::Loop() {
  while (!quit) {
    SDL_RenderClear(renderer);
    race.Step();
    view.render();
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }
}

void UpdateLoop::Start() {
  t = std::thread(&UpdateLoop::Loop, this);
}

void UpdateLoop::Join() {
  if (t.joinable()) t.join();
}