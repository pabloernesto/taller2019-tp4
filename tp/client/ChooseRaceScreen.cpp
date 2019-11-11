#include "ChooseRaceScreen.h"
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"

#define SPACEBETWEENBUTTONS 10
#define TITLESIZEPERLETTER 35
#define BUTTONSIZEPERLETTER 27

#define WIDTH 640
#define HEIGHT 480

ChooseRaceScreen::ChooseRaceScreen(SDL_Window *w, SDL_Renderer *r) 
  : GameScreen(w, r), buttons() {
    TTF_Init();
  }

ChooseRaceScreen::~ChooseRaceScreen(){
  TTF_Quit();
}

GameScreen* ChooseRaceScreen::start(){
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_RenderClear(renderer);
  SDL_Event sdl_event;

  showMessage("x", TITLESIZEPERLETTER, 0, 0);

  //Agrego el titulo
  int xButton = WIDTH/2;
  int yButton = TITLESIZEPERLETTER/2;
  showMessage("Choose a race..", TITLESIZEPERLETTER, xButton, yButton);
  yButton += SPACEBETWEENBUTTONS + TITLESIZEPERLETTER;

  //agrego los botones
  buttons.emplace_back(new Button("race 1", BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER, "6 9 666662004204661661163005661166666661162004661305663005"));
  buttons.emplace_back(new Button("race 2", BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER, "5 4 20041205116611663566"));
  std::vector<std::unique_ptr<Button>>::iterator it = buttons.begin();
  for (; it != buttons.end(); ++it, yButton += SPACEBETWEENBUTTONS + BUTTONSIZEPERLETTER) {
    (*it)->SetPosition(xButton, yButton);
    showMessage((*it)->GetName(), BUTTONSIZEPERLETTER, xButton, yButton);
  }
  SDL_RenderPresent(renderer);

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.button.button == SDL_BUTTON_LEFT){ //Boton izquierdo del mouse
	    Sint32 x = sdl_event.button.x;
      Sint32 y = sdl_event.button.y;
      std::vector<std::unique_ptr<Button>>::iterator it = buttons.begin();
      for (; it != buttons.end(); ++it, yButton += SPACEBETWEENBUTTONS + BUTTONSIZEPERLETTER) {
        if ((*it)->IWasClicked(x,y)){
          std::string race = (*it)->GetRace();
          return new RaceScreen(window, renderer, race);
        }
      }
    }
    SDL_RenderPresent(renderer);
  }

  return nullptr;
}

void ChooseRaceScreen::showMessage(std::string message, int size, int x, int y){
  TTF_Font* font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  int width = size * (int)message.size();
  SDL_Rect Message_rect = {x - width/2, y - size/2, width, size};
  printf("render: x: %d y: %d\n", x - width/2, y - size/2);

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(font);
}