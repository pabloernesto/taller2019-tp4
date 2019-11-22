#include "Podium.h"
#include "ChooseRaceScreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GoToChooseRaceScreen.h"
#include <iostream>
#include "../common/Configuration.h"
#include "TextPrinter.h"

#define ENDSIGNSIZE 70
#define BUTTONSIZE 20
#define FONT "MAKISUPA.TTF"

extern Configuration configuration;

Podium::Podium(SDL_Window *w, SDL_Renderer *r, bool winner)
  : GameScreen(w, r), winner(winner), 
  font(TTF_OpenFont((configuration.FONTS_ROUTE + FONT).c_str(), 50)),
  next_screen() {}

Podium::~Podium(){}

GameScreen* Podium::start(){
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Event sdl_event;

  std::string name = "Play again";
  int widthButton = (int)name.size()*BUTTONSIZE;
  GoToChooseRaceScreen chooseRace(nullptr, window, renderer, 
    {configuration.WINDOW_WIDTH/2 - widthButton/2, 
    configuration.WINDOW_HEIGHT - BUTTONSIZE, 
    widthButton, BUTTONSIZE}, name, 
    font, {225,225,225}, this);

  TextPrinter printer(font);
  if (winner){
    printer.showMessage("GANASTE",ENDSIGNSIZE,configuration.WINDOW_WIDTH/2,ENDSIGNSIZE/2,renderer);
  } else {
    printer.showMessage("PERDISTE",ENDSIGNSIZE,configuration.WINDOW_WIDTH/2,ENDSIGNSIZE/2,renderer);
  }

  chooseRace.render();

  SDL_RenderPresent(renderer);

  while (!next_screen) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
      chooseRace.Handle(&sdl_event);
  }

  return next_screen;
}
