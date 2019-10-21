#include "RaceScreen.h"
#include "../common/Track.h"
#include <vector>

static const int WIDTH = 600;
static const int HEIGHT = 300;
enum trackTypes{
  PASTO,
  HORIZONTAL,
  VERTICAL,
  GIRO_ARRIBADER,
  GIRO_ABAJODER,
  GIRO_ARRIBAIZQ,
  GIRO_ABAJOIZQ
};

GameScreen* RaceScreen::start() {
  SDL_SetWindowSize(window, WIDTH, HEIGHT);

  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    std::vector<int> blocks = {GIRO_ARRIBADER,GIRO_ARRIBAIZQ,
      GIRO_ABAJODER,GIRO_ABAJOIZQ};
    Track track((uint16_t)2,(uint16_t)2,blocks);
    track.render(window, renderer);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  return nullptr;
}
