#include "Podium.h"
#include "ChooseRaceScreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GoToChooseRaceScreen.h"
#include <iostream>
#include "../common/Configuration.h"

#define ENDSIGNSIZE 70
#define BUTTONSIZE 20

extern Configuration configuration;

Podium::Podium(SDL_Window *w, SDL_Renderer *r, bool winner)
  : GameScreen(w, r), winner(winner), next_screen(){}

GameScreen* Podium::start(){
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Event sdl_event;
  TTF_Font* font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);

  std::string name = "Play again";
  int widthButton = (int)name.size()*BUTTONSIZE;
  GoToChooseRaceScreen chooseRace(nullptr, window, renderer, 
    {configuration.WINDOW_WIDTH/2 - widthButton/2, 
    configuration.WINDOW_HEIGHT - BUTTONSIZE, 
    widthButton, BUTTONSIZE}, name, 
    font, {225,225,225}, this);

  if (winner){
    showMessage("GANASTE",ENDSIGNSIZE,configuration.WINDOW_WIDTH/2,ENDSIGNSIZE/2);
  } else {
    showMessage("PERDISTE",ENDSIGNSIZE,configuration.WINDOW_WIDTH/2,ENDSIGNSIZE/2);
  }

  chooseRace.render();

  SDL_RenderPresent(renderer);

  while (!next_screen) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
      chooseRace.Handle(&sdl_event);
  }

  TTF_CloseFont(font);
  return next_screen;
}

void Podium::showMessage(std::string message, int size, int x, int y){
  TTF_Font* font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  int width = size * (int)message.size();
  SDL_Rect Message_rect = {x - width/2, y - size/2, width, size};

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
  TTF_CloseFont(font);
}
