#include "ChooseRaceScreen_Buttons.h"
#include <SDL2/SDL.h>
#include "ChooseRaceScreen.h"
#include "RaceScreen.h"
#include "RaceProxy.h"
#include <stdexcept>  // runtime_error
#include <iostream>

bool RaceButton::OnHandle(void* t) {
  // Create the game
  rapidjson::Document d;
  {
    context->connection.SendStr(msg.c_str());
    char* data = context->connection.GetStr();
    d.Parse(data);
    delete[] data;
  }

  // Build the race
  RaceProxy* proxy = new RaceProxy(d["track"], std::move(context->connection));
  proxy->Start();

  // Build the next screen
  int id_player = d["id"].GetInt();
  context->next_screen = new RaceScreen(window, renderer, proxy, id_player);
  return false;
}



// Constructors/destructors

RaceButton::RaceButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  ChooseRaceScreen* context, std::string msg)
  : TextButton(next, w, r, area, text, font, color), context(context),
  msg(std::move(msg))
{}


CreateButton::CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  ChooseRaceScreen* context)
  : RaceButton(next, w, r, area, text, font, color, context,
  "{\"type\": \"c\"}")
{}

JoinButton::JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  int id_game, ChooseRaceScreen* context)
  : RaceButton(next, w, r, area, text, font, color, context,
  "{\"type\": \"j\", \"id\":" + std::to_string(id_game) + "}")
{}
