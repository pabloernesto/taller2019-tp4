#include "UpdateLoop.h"

#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_until

static const int FRAMERATE = 60;

UpdateLoop::UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v)
  : renderer(ren), race(r), view(v), t(), quit(false)
{}

void UpdateLoop::Loop() {
  const auto rate = std::chrono::milliseconds(1000 / FRAMERATE);
  auto time = std::chrono::system_clock::now();

  while (!quit) {
    SDL_RenderClear(renderer);
    race.Step();
    view.render();
    SDL_RenderPresent(renderer);

    // Frame rate limiting
    time += rate;
    std::this_thread::sleep_until(time);
  }
}

void UpdateLoop::Start() {
  t = std::thread(&UpdateLoop::Loop, this);
}

void UpdateLoop::Join() {
  if (t.joinable()) t.join();
}