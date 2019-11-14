#include "ButtonJoinRace.h"

ButtonJoinRace::ButtonJoinRace(std::string name, int width, int height, int index, rapidjson::Value&& game)
  : Button(name, width, height), game(std::move(game)), index(index){}

int ButtonJoinRace::ReactToClick(int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    std::string join = "{\"type\":\"j\",\"id\":" + std::to_string(index) + "}";
    connection.SendStr(join.c_str());
    int id_player;
    {
      char* data = connection.GetStr();
      id_player = atoi(data);
      delete[] data;
    }
    return id_player;
  }
  return -1;
}

rapidjson::Value& ButtonJoinRace::GetGame(){
  return game;
}

int ButtonJoinRace::GetIndex(){
  return index;
}