#include "Podium.h"
#include "ChooseRaceScreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define WIDTH 640
#define HEIGHT 480
#define ENDSIGNSIZE 70
#include <iostream>

Podium::Podium(SDL_Window *w, SDL_Renderer *r, bool winner)
  : GameScreen(w, r), winner(winner){}

GameScreen* Podium::start(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Event sdl_event;

  if (winner){
    showMessage("GANASTE",ENDSIGNSIZE,WIDTH/2,ENDSIGNSIZE/2);
  } else {
    showMessage("PERDISTE",ENDSIGNSIZE,WIDTH/2,ENDSIGNSIZE/2);
  }
  SDL_RenderPresent(renderer);

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;
    if (sdl_event.type == SDL_KEYDOWN)
      if (sdl_event.key.keysym.sym == SDLK_DOWN) break;
  }

  return new ChooseRaceScreen(window,renderer);
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
