#include "RaceProxy.h"
#define BQSIZE 100

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
      if (!this->IHaveCarWithId(msg["id"].GetInt())){
        cars.emplace_back(new CarProxy(ec.GetOutgoingQueue(), msg["position.x"].GetFloat(), msg["position.y"].GetFloat(), 
          msg["angle"].GetFloat(), msg["size.x"].GetFloat(), msg["size.y"].GetFloat(), 
          msg["id"].GetInt()));
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

bool RaceProxy::IHaveCarWithId(int id){
  auto it = cars.begin();
  for (; it != cars.end(); ++it){
    if((*it)->GetId() == id){
      return true;
    }
  }
  return false;
}