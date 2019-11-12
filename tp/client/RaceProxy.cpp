#include "RaceProxy.h"
#define BQSIZE 100
#define DEFAULTPOSITIONX 0
#define DEFAULTPOSITIONY 0
#define DEFAULTSIZEX 1
#define DEFAULTSIZEY 1
#define DEFAULTANGLE 0

RaceProxy::RaceProxy(std::string track, Connection& connection) : 
  connection(connection), bq(BQSIZE), ec(std::move(connection), bq),
  cars(), modifiers() {}

void RaceProxy::UpdateLoop() {
  while (true) {
    std::string str;
    if (!ec.GetIncomingQueue().trypop(&str))
      ; // tirar error
    rapidjson::Document msg;
    msg.Parse(str.c_str());
    
    if (msg["type"] == "car") {
      CarProxy* car = this->GetCarWithId(msg["id"].GetInt());
      if (!car){
        cars.emplace_back(new CarProxy(ec.GetOutgoingQueue(), msg["position.x"].GetFloat(), msg["position.y"].GetFloat(), 
          msg["angle"].GetFloat(), msg["size.x"].GetFloat(), msg["size.y"].GetFloat(), 
          msg["id"].GetInt()));
      } else {
        car->update(
          msg["position.x"].GetFloat(), msg["position.y"].GetFloat(), 
          msg["angle"].GetFloat(),
          msg["size.x"].GetFloat(), msg["size.y"].GetFloat(),
          msg["dead"].GetBool());
      }
    } else if (msg["type"] == "modifier") {
      auto list = msg["data"].GetArray();
      modifiers.clear();
      rapidjson::Value::Array::ValueIterator it = list.begin();
      for (;it != list.end(); ++it){
        auto modifier = it->GetObject();
        modifiers.emplace_back(new ModifierProxy(modifier["position.x"].GetFloat(),modifier["position.y"].GetFloat(),
          modifier["size.x"].GetFloat(), modifier["size.x"].GetFloat(), 
          modifier["modifier.type"].GetString()));
      }
    }
  }
}

void RaceProxy::Start() {
  t = std::thread(&RaceProxy::UpdateLoop, this);
}

CarProxy* RaceProxy::GetCar(int id){
  auto it = cars.begin();
  for (; it != cars.end(); ++it){
    if((*it)->GetId() == id){
      return it->get();
    }
  }
  cars.emplace_back(new CarProxy(ec.GetOutgoingQueue(), DEFAULTPOSITIONX, DEFAULTPOSITIONY, 
    DEFAULTANGLE, DEFAULTSIZEX, DEFAULTSIZEY, id));
  return cars.back().get();
}

std::vector<std::unique_ptr<TrackPieceProxy>>& getTrackPieces(){
  return this->tracks;
}

CarProxy* RaceProxy::GetCarWithId(int id){
  auto it = cars.begin();
  for (; it != cars.end(); ++it){
    if((*it)->GetId() == id){
      return it->get();
    }
  }
  return nullptr;
}

std::vector<std::unique_ptr<CarProxy>>& RaceProxy::GetCars() {
  return cars;
}

std::vector<std::unique_ptr<ModifierProxy>>& RaceProxy::getModifiers(){
  return this->modifiers;
}