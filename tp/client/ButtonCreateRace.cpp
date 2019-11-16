#include "ButtonCreateRace.h"

ButtonCreateRace::ButtonCreateRace(std::string name, int width, int height)
  : Button(name, width, height){}

RaceProxy* ButtonCreateRace::ReactToClick(int* id_player, int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    std::string join = "{\"type\":\"c\"}";
    connection.SendStr(join.c_str());
    rapidjson::Document game;
    char* data = connection.GetStr();
    game.Parse(data);
    *id_player = game["id"].GetInt();
    auto& track = game["track"];
    RaceProxy* race = new RaceProxy(track, std::move(connection));
    return race;
  }
  *id_player = -1;
  return nullptr;
}