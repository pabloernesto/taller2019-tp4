#include "RaceScreen.h"
#include "../common/Track.h"
#include <vector>
#include "UpdateLoop.h"
#include "../common/Camara.h"
#include <iostream>
#include <math.h>

static const int WIDTH = 600;
static const int HEIGHT = 400;

RaceScreen::~RaceScreen(){
}

RaceScreen::RaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), race("6 9 666662004204661661163005661166666661162004661305663005 ", 1)
{}

GameScreen* RaceScreen::start() {
  SDL_Event sdl_event;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // Agrego postas
  race.AddPosta(5,-20,0,0);
  race.AddPosta(55,-20,1,0);
  race.AddPosta(80,-5,2,-M_PI/2);
  race.AddPosta(55,-50,3,0);
  race.AddPosta(5,-50,4,0);

  race.AddCar(0,-20, 1); //para probar que puede mostrar varios autos a la vez
  race.AddCar(3,-20, 2); //para probar que puede mostrar varios autos a la vez
  RaceView view(this->window, this->renderer, race, race.AddCar(7,-20, 3));
  //auto&& car = *(race.GetCars()[0]);
  auto&& car = *(race.GetCars()[2]);

  UpdateLoop loop(renderer, race, view);
  loop.Start();

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      switch(sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
          car.SteerLeft();
          break;
        case SDLK_RIGHT:
          car.SteerRight();
          break;
        case SDLK_UP:
          if (!car.isGoingForward()){
            car.BreakOn();
          } else {
            car.BreakOff();
            car.GasOn();
          }
          break;
        case SDLK_DOWN:
          if (car.isGoingForward()){
            car.BreakOn();
          } else {
            car.BreakOff();
            car.reverseOn();
            car.GasOn();
          }
          break;
        default:
          break;
      }
    }
    if (sdl_event.type == SDL_KEYUP) {
      switch(sdl_event.key.keysym.sym) {
        case SDLK_LEFT:
          car.SteerCenter();
          break;
        case SDLK_RIGHT:
          car.SteerCenter();
          break;
        case SDLK_UP:
          car.GasOff();
          car.BreakOff();
          break;
        case SDLK_DOWN:
          car.BreakOff();
          car.GasOff();
          car.reverseOff();
          break;
      default:
        break;
      }
    }
  }

  loop.quit = true;
  loop.Join();

  return nullptr;
}
