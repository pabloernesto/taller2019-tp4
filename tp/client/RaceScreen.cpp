#include "RaceScreen.h"
#include "../common/Track.h"
#include "../common/image.h"
#include <vector>

static const int WIDTH = 600;
static const int HEIGHT = 300;
enum trackTypes{
  HORIZONTAL,
  VERTICAL,
  GIRO_ARRIBADER,
  GIRO_ABAJODER,
  GIRO_ARRIBAIZQ,
  GIRO_ABAJOIZQ,
  PASTO
};

RaceScreen::RaceScreen(SDL_Window* &w, SDL_Renderer* &r): GameScreen(w,r){
}

RaceScreen::~RaceScreen(){
}

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  Image fondo("Imagenes/pasto.bmp",this->window, this->renderer);
  //SDL_SetWindowSize(window, WIDTH, HEIGHT);

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

///////////////////
    /*std::vector<int> blocks = {GIRO_ARRIBADER,GIRO_ARRIBAIZQ,
      GIRO_ABAJODER,GIRO_ABAJOIZQ};
    Track track(2, 2, blocks);*/
///////////////////
    Track track("2 2 2435");

    SDL_RenderClear(this->renderer);
    fondo.render(0, 0, HEIGHT, WIDTH);
    track.render(this->window, this->renderer);
    SDL_RenderPresent(this->renderer);
  }
  return nullptr;
}
