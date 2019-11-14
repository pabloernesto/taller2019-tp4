#include "ButtonCreateRace.h"

ButtonCreateRace::ButtonCreateRace(std::string name, int width, int height)
  : Button(name, width, height){}

int ButtonCreateRace::ReactToClick(int x, int y, Connection& connection){
  if (this->IWasClicked(x, y)){
    printf("fue clickeado\n");
    std::string join = "{\"type\":\"c\"}";
    connection.SendStr(join.c_str());
    int id_player;
    {
      char* data = connection.GetStr();
      id_player = atoi(data);
      delete[] data;
    }
    printf("id: %d\n", id_player);
    return id_player;
  }
  return -1;
}