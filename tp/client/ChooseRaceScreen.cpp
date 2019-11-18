#include "ChooseRaceScreen.h"
#include <SDL2/SDL_ttf.h>
#include "RaceScreen.h"
#include "../common/socket.h"
#include "rapidjson/document.h"
#include <iostream>
#include "ChooseRaceScreen_Buttons.h"

#define SPACEBETWEENBUTTONS 10
#define TITLESIZEPERLETTER 35
#define BUTTONSIZEPERLETTER 27

#define WIDTH 600
#define HEIGHT 400

ChooseRaceScreen::ChooseRaceScreen(SDL_Window *w, SDL_Renderer *r)
  : GameScreen(w, r), button_chain(), font(),
  next_screen(), connection("localhost", "1234")
{
  font = TTF_OpenFont("Fuentes/MAKISUPA.TTF", 50);
}

ChooseRaceScreen::~ChooseRaceScreen(){
  TTF_CloseFont(font);
}

void ChooseRaceScreen::GetGames(Connection& connection, rapidjson::Document* race_list){
  connection.SendStr("{\"type\":\"l\"}");
  {
    char* data = connection.GetStr();
    race_list->Parse(data);
    delete[] data;
  }

  // x is screen center
  int x;
  SDL_GetWindowSize(window, &x, NULL);
  x /= 2;

  // y is some ways from the top + constant * buttons.size
  int y = 70;

  const SDL_Color color = { 255, 255, 255 };
  const int button_w = 150;
  const int button_h = 40;

  auto it_games = race_list->Begin();
  for (; it_games != race_list->End(); ++it_games){
    auto game = it_games->GetObject();
    int id_game = game["id"].GetInt();
    std::string text = "Game " + std::to_string(id_game);
    SDL_Rect area = {
      x - button_w/2,   y - button_h/2,
      button_w,         button_h
    };
    button_chain.reset(new JoinButton(
      button_chain.release(), window, renderer, area, text, font, color,
      id_game, this));
    y += 50;
  }

  SDL_Rect area = {
    x - button_w/2,   y - button_h/2,
    button_w,         button_h
  };
  button_chain.reset(new CreateButton(
    button_chain.release(), window, renderer, area, "New Game", font, color,
    this));
}

void ChooseRaceScreen::DrawWindow(){
  //Agrego el titulo
  int xButton = WIDTH/2;
  int yButton = TITLESIZEPERLETTER/2;
  showMessage("Choose a race..", TITLESIZEPERLETTER, xButton, yButton);
  yButton += SPACEBETWEENBUTTONS + TITLESIZEPERLETTER;

  // Muestro los botones
  button_chain->render();
}

GameScreen* ChooseRaceScreen::start(){
  int w;
  int h;
  SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_GL_GetDrawableSize(window, &w, &h);
  SDL_RenderSetLogicalSize(renderer, w, h);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Event sdl_event;

  rapidjson::Document race_list;

  // Populate button_chain
  this->GetGames(connection, &race_list);

  DrawWindow();
  SDL_RenderPresent(renderer);

  while (!next_screen) {
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    // NOTE: Handle() may alter ChooseRaceScreen::next_screen
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
      button_chain->Handle(&sdl_event);

    SDL_RenderClear(renderer);
    DrawWindow();
    SDL_RenderPresent(renderer);
  }

  return next_screen;
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