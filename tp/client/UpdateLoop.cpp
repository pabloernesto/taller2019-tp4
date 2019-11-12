#include "UpdateLoop.h"

#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for

static const int FRAMERATE = 60;

UpdateLoop::UpdateLoop(SDL_Renderer* ren, std::unique_ptr<RaceProxy>& r, RaceView& v)
  : renderer(ren), race(r), view(v), t(), quit(false)
{}

void UpdateLoop::Loop() {
  const auto rate = std::chrono::milliseconds(1000 / FRAMERATE);
  auto time1 = std::chrono::system_clock::now();
  int tick = 0;

  while (!quit) {
    SDL_RenderClear(renderer);
    view.render(tick);
    SDL_RenderPresent(renderer);

    // Frame rate limiting
    const auto time2 = std::chrono::system_clock::now();
    auto rest = rate - (time2 - time1);
    if (rest.count() < 0) {
      const auto behind = -rest;
      const auto lost = behind - behind % rate;
      rest = rate - behind % rate;
      time1 += lost;
      tick += lost / rate;
    }

    tick++;
    time1 += rate;
    std::this_thread::sleep_for(rest);
  }
}

void UpdateLoop::Start() {
  t = std::thread(&UpdateLoop::Loop, this);
}

void UpdateLoop::Join() {
  if (t.joinable()) t.join();
}