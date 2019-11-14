#include "StartGameController.h"
#include "rapidjson/document.h"

StartGameController::StartGameController(TaskHandler* next, Game& game) : 
                              TaskHandler(next), game(game){}

bool StartGameController::ShouldHandle(void* t){
  rapidjson::Document* d = (rapidjson::Document*) t;
  std::string type = (*d)["type"].GetString();
  return type == "s";
}

bool StartGameController::OnHandle(void* t){
  rapidjson::Document* d = (rapidjson::Document*) t;
  int id = (*d)["id"].GetInt();
  this->game.startGame(id);
  return false;
}