#include "RaceProxy.h"
#include "../common/string.h"
#include <iostream>
#define BQSIZE 100
#define DEFAULTPOSITIONX 0
#define DEFAULTPOSITIONY 0
#define DEFAULTSIZEX 1
#define DEFAULTSIZEY 1
#define DEFAULTANGLE 0

RaceProxy::RaceProxy(rapidjson::Value& track, Connection&& connection) :
  bq(BQSIZE), ec(std::move(connection), bq), cars(), modifiers(), ended(false),
  winner_id(-1) {
  auto arr = track.GetArray();
  for (auto it = arr.Begin(); it != arr.End(); ++it) {
    auto piece = it->GetObject();
    this->tracks.emplace_back(new TrackPieceProxy(piece["type"].GetInt(), piece["pos.x"].GetFloat(),
      piece["pos.y"].GetFloat(), piece["size.x"].GetFloat(), piece["size.y"].GetFloat()));
  }
}

void RaceProxy::UpdateCar(rapidjson::Document& msg){
  std::lock_guard<std::mutex> lock(cars_mtx);
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
}

void RaceProxy::UpdateModifiers(rapidjson::Document& msg){
  auto list = msg["data"].GetArray();
  std::lock_guard<std::mutex> lock(modifiers_mtx);
  modifiers.clear();
  rapidjson::Value::Array::ValueIterator it = list.begin();
  for (;it != list.end(); ++it){
    auto modifier = it->GetObject();
    modifiers.emplace_back(new ModifierProxy(modifier["position.x"].GetFloat(),modifier["position.y"].GetFloat(),
      modifier["size.x"].GetFloat(), modifier["size.x"].GetFloat(),
      modifier["modifier.type"].GetString()));
  }
}

void RaceProxy::UpdateRace(rapidjson::Document& msg){
  ended = msg["ended"].GetBool();
  winner_id = msg["winner_id"].GetBool();
}

void RaceProxy::UpdateLoop() {
  while (true) {
    std::string str;
    if (!ec.GetIncomingQueue().trypop(&str))
      ; // tirar error
    rapidjson::Document msg;
    msg.Parse(str.c_str());

    if (msg.HasMember("error")) {
      throw std::runtime_error(msg["error"].GetString());
    } else if (std::string(msg["type"].GetString()) == "car") {
      UpdateCar(msg);
    } else if (std::string(msg["type"].GetString()) == "modifier") {
      UpdateModifiers(msg);
    } else if (std::string(msg["type"].GetString()) == "race") {
      UpdateRace(msg);
    }
  }
}

void RaceProxy::Start() {
  t = std::thread(&RaceProxy::UpdateLoop, this);
}

CarProxy* RaceProxy::GetCar(int id){
  std::lock_guard<std::mutex> lock(cars_mtx);
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

std::vector<std::unique_ptr<TrackPieceProxy>>& RaceProxy::getTrackPieces(){
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

std::vector<ModifierProxy> RaceProxy::getModifiers(){
  std::lock_guard<std::mutex> lock(modifiers_mtx);
  std::vector<ModifierProxy> v;
  for (auto& uptr : modifiers)
    v.emplace_back(*uptr);
  return v;
}

bool RaceProxy::Ended(){
  return ended;
}

int RaceProxy::GetWinnerId(){
  return winner_id;
}

void RaceProxy::SendToServer(std::string&& msg) {
  ec.GetOutgoingQueue().push(std::move(msg));
}
