#include "ChooseRaceScreen.h"
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include "../common/RaceFabric.h"
#include "../common/socket.h"
#include "rapidjson/document.h"
#include <iostream>

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

  //Agrego el titulo
  int xButton = WIDTH/2;
  int yButton = TITLESIZEPERLETTER/2;
  showMessage("Choose a race..", TITLESIZEPERLETTER, xButton, yButton);
  yButton += SPACEBETWEENBUTTONS + TITLESIZEPERLETTER;

  // Obtener la lista de carreras
  Connection connection("localhost", "1234");
  connection.SendStr("{\"type\":\"l\"}");
  rapidjson::Document race_list;
  {
    char* data = connection.GetStr();
    race_list.Parse(data);
    delete[] data;
  }

  buttons.emplace_back(new Button("race 1", BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER, 0));
  buttons.emplace_back(new Button("race 2", BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER, 1));
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
      std::cerr << "CHECKPOINT\n";
	    Sint32 x = sdl_event.button.x;
      Sint32 y = sdl_event.button.y;
      std::vector<std::unique_ptr<Button>>::iterator it = buttons.begin();
      for (; it != buttons.end(); ++it, yButton += SPACEBETWEENBUTTONS + BUTTONSIZEPERLETTER) {
        if ((*it)->IWasClicked(x,y)){
          connection.SendStr("{\"type\":\"j\",\"id\":0}");
          int id_player;
          {
            char* data = connection.GetStr();
            id_player = atoi(data);
            delete[] data;
          }
          RaceProxy* raceProxy = new RaceProxy(
            race_list[0]["track"].GetString(),
            std::move(connection));
          raceProxy->Start();
          return new RaceScreen(window, renderer, raceProxy, id_player);
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

  SDL_RenderCopyEx(renderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(font);
}