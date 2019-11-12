#include "CarProxy.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

CarProxy::CarProxy(BlockingQueue<std::string>& outqueue, float x, float y, 
                      float angle, float size_x, float size_y) : 
                      outqueue(outqueue), x(x), y(y), angle(angle),
                      size_x(size_x), size_y(size_y), dead(false){}

void CarProxy::sendMethod(std::string method){
  rapidjson::Document d;
  d.AddMember("type", "intent", d.GetAllocator());
  rapidjson::Value command (method.c_str(), d.GetAllocator());
  d.AddMember("command", command, d.GetAllocator());
  
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);
  outqueue.push(buffer.GetString());
}

void CarProxy::update(float x, float y, float angle, bool dead){
  this->x = x;
  this->y = y;
  this->angle = angle;
  this->dead = dead;
}

std::vector<float> CarProxy::GetPosition(){
  std::vector<float> v;
  v.push_back(this->x);
  v.push_back(this->y);
  return v; 
}

std::vector<float> CarProxy::GetSize(){
  std::vector<float> v;
  v.push_back(this->size_x);
  v.push_back(this->size_y);
  return v;
}

void CarProxy::GasOn(){
  this->sendMethod("GasOn");
}

void CarProxy::GasOff(){
  this->sendMethod("GasOff");
}

void CarProxy::BreakOn(){
  this->sendMethod("BreakOn");
}

void CarProxy::BreakOff(){
  this->sendMethod("BreakOff");
}

void CarProxy::SteerRight(){
  this->sendMethod("SteerRight");
}

void CarProxy::SteerLeft(){
  this->sendMethod("SteerLeft");
}

bool CarProxy::isDead(){
  return this->dead;
}

void CarProxy::SteerCenter(){
  this->sendMethod("SteerCenter");
}