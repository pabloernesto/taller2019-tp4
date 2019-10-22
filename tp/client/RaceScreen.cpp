#include "RaceScreen.h"

#include <thread>
#include <atomic>

static const int WIDTH = 600;
static const int HEIGHT = 300;

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), race(), view(w, r, race)
{}

class UpdateLoop {
  SDL_Renderer* renderer;
  Race& race;
  RaceView& view;
  std::thread t;

  void Loop() {
    while (!quit) {
      SDL_RenderClear(renderer);
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

GameScreen* RaceScreen::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  race.AddCar();

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  // TODO: check SDL_QUIT event
  SDL_Delay(3000);

  loop.quit = true;
  loop.Join();

  return nullptr;
}
