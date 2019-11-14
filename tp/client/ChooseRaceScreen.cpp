#include "ChooseRaceScreen.h"
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include "../common/RaceFabric.h"
#include "../common/socket.h"
#include "rapidjson/document.h"
#include <iostream>
#include "ButtonCreateRace.h"

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

void ChooseRaceScreen::GetGames(Connection& connection, rapidjson::Document* race_list){
  connection.SendStr("{\"type\":\"l\"}");
  {
    char* data = connection.GetStr();
    race_list->Parse(data);
    delete[] data;
  }
  auto it_games = race_list->Begin();
  for (; it_games != race_list->End(); ++it_games){
    auto game = it_games->GetObject();
    int id_game = game["id"].GetInt();
    buttons.emplace_back(new ButtonJoinRace("race " + std::to_string(id_game), 
                                    BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER, 
                                    id_game, std::move(*it_games)));
  }
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

  Connection connection("localhost", "1234");
  rapidjson::Document race_list;
  this->GetGames(connection, &race_list);

  //Muestro los botones de races
  std::vector<std::unique_ptr<ButtonJoinRace>>::iterator it = buttons.begin();
  for (; it != buttons.end(); ++it, yButton += SPACEBETWEENBUTTONS + BUTTONSIZEPERLETTER) {
    (*it)->SetPosition(xButton, yButton);
    showMessage((*it)->GetName(), BUTTONSIZEPERLETTER, xButton, yButton);
  }

  //Muestro el boton de crear race
  ButtonCreateRace createRace("Create", BUTTONSIZEPERLETTER, BUTTONSIZEPERLETTER);
  createRace.SetPosition(xButton, yButton);
  showMessage(createRace.GetName(), BUTTONSIZEPERLETTER, xButton, yButton);

  SDL_RenderPresent(renderer);

  while (true) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.button.button == SDL_BUTTON_LEFT){ //Boton izquierdo del mouse
	    Sint32 x = sdl_event.button.x;
      Sint32 y = sdl_event.button.y;
      std::vector<std::unique_ptr<ButtonJoinRace>>::iterator it = buttons.begin();
      for (; it != buttons.end(); ++it, yButton += SPACEBETWEENBUTTONS + BUTTONSIZEPERLETTER) {
        int id_player = (*it)->ReactToClick(x, y, connection);
        if (id_player != -1){
          RaceProxy* raceProxy = new RaceProxy(
            (*it)->GetGame(),
            std::move(connection));
          raceProxy->Start();
          return new RaceScreen(window, renderer, raceProxy, id_player+1);
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