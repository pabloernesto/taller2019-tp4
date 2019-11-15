#include "ButtonCreateRace.h"

ButtonCreateRace::ButtonCreateRace(std::string name, int width, int height)
  : Button(name, width, height){}

RaceProxy* ButtonCreateRace::ReactToClick(int* id_player, int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    printf("fue clickeado\n");
    std::string join = "{\"type\":\"c\"}";
    connection.SendStr(join.c_str());
    rapidjson::Document game;
    char* data = connection.GetStr();
    game.Parse(data);
    *id_player = game["id"].GetInt();
    auto track = game["track"].GetObject();
    RaceProxy* race = new RaceProxy(game, std::move(connection));
    printf("id: %d\n", *id_player);
    return race;
  }
  return nullptr;
}