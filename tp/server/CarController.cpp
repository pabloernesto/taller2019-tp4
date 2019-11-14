#include "CarController.h"
#include "rapidjson/document.h"

CarController::CarController(TaskHandler* next, Car& car) : TaskHandler(next), car(car){}

/* msg example:

{
  "type" : "intent",
  "id" : 4,
  "command" : "GasOn"
}

*/


bool CarController::ShouldHandle(void* t){
  rapidjson::Document* d = (rapidjson::Document*) t;
  std::string type = (*d)["type"].GetString();
  if (type == "intent"){
    int id = (*d)["id"].GetInt();
    //Esta bien el GetInt o tiene que ser un GetString?
    return id == car.GetId();
  }
  return false;
}

bool CarController::OnHandle(void* t){
  rapidjson::Document* d = (rapidjson::Document*) t;
  std::string command = (*d)["command"].GetString();
  if (command == "GasOn"){
    this->car.GasOn();
  } else if (command == "GasOff"){
    this->car.GasOff();
  } else if (command == "BreakOn"){
    this->car.BreakOn();
  } else if (command == "BreakOff"){
    this->car.BreakOff();
  } else if (command == "SteerCenter"){
    this->car.SteerCenter();
  } else if (command == "SteerLeft"){
    this->car.SteerLeft();
  } else if (command == "SteerRight"){
    this->car.SteerRight();
  } else {
    throw std::runtime_error("Bad command " + command);
  }
  return false; 
}
