#include "RaceScreen.h"
#include <vector>

#include <thread>
#include <atomic>
#include <vector>

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

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

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  race.AddCar();

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  // TODO: check SDL_QUIT event
  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    view.reactTo(sdl_event);/////////////////////////////////
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}
