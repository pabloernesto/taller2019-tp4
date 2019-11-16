#include "ChooseRaceScreen_Buttons.h"
#include <SDL2/SDL.h>
#include "ChooseRaceScreen.h"
#include "RaceScreen.h"
#include "RaceProxy.h"

bool CreateButton::OnHandle(void* t) {
  // Create the game
  rapidjson::Document d;
  {
    std::string msg = "{\"type\":\"c\"}";
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

bool JoinButton::OnHandle(void* t) {
  // Join the game
  rapidjson::Document d;
  {
    std::string msg = "{\"type\":\"j\",\"id\":" + std::to_string(id_game) + "}";
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

CreateButton::CreateButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  ChooseRaceScreen* context)
  : TextButton(next, w, r, area, text, font, color),
  context(context)
{}

JoinButton::JoinButton(TaskHandler* next, SDL_Window* w, SDL_Renderer* r,
  SDL_Rect area, std::string text, TTF_Font* font, SDL_Color color,
  int id_game, ChooseRaceScreen* context)
  : TextButton(next, w, r, area, text, font, color),
  id_game(id_game), context(context)
{}
