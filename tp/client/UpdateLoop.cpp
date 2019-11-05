#include "UpdateLoop.h"

#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_until

static const int FRAMERATE = 60;

UpdateLoop::UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v)
  : renderer(ren), race(r), view(v), t(), quit(false)
{}

void UpdateLoop::Loop() {
  const auto rate = std::chrono::milliseconds(1000 / FRAMERATE);
  auto time1 = std::chrono::system_clock::now();
  int tick = 0;

  while (!quit) {
    SDL_RenderClear(renderer);
    race.Step();
    view.render(tick);
    SDL_RenderPresent(renderer);

    // Frame rate limiting
    const auto time2 = std::chrono::system_clock::now();
    const auto delta = time2 - time1;
    const auto frames = delta / rate;
    tick += frames;

    time1 += rate;
    std::this_thread::sleep_until(time1);
  }
}

void UpdateLoop::Start() {
  t = std::thread(&UpdateLoop::Loop, this);
}

void UpdateLoop::Join() {
  if (t.joinable()) t.join();
}