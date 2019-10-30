#include "UpdateLoop.h"

static const int FRAMERATE = 60;

UpdateLoop::UpdateLoop(SDL_Renderer* ren, Race& r, RaceView& v, Camara& camara)
  : renderer(ren), race(r), view(v), t(), quit(false), camara(camara)
{}

void UpdateLoop::Loop() {
  while (!quit) {
    SDL_RenderClear(renderer);
    race.Step();
    camara.Update();
    view.render(camara.GetPosition(), camara);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FRAMERATE);
  }
}

void UpdateLoop::Start() {
  t = std::thread(&UpdateLoop::Loop, this);
}

void UpdateLoop::Join() {
  if (t.joinable()) t.join();
}