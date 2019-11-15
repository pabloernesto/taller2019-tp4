#include "ButtonJoinRace.h"

ButtonJoinRace::ButtonJoinRace(std::string name, int width, int height, int index)
  : Button(name, width, height), index(index){}

RaceProxy* ButtonJoinRace::ReactToClick(int* id_player, int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    std::string join = "{\"type\":\"j\",\"id\":" + std::to_string(index) + "}";
    connection.SendStr(join.c_str());
    rapidjson::Document game;
    char* data = connection.GetStr();
    game.Parse(data);
    *id_player = game["id"].GetInt();
    auto& track = game["track"];
    RaceProxy* race = new RaceProxy(track, std::move(connection));
    return race;
  }
  return nullptr;
}

int ButtonJoinRace::GetIndex(){
  return index;
}