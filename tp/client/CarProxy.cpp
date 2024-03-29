#include "CarProxy.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

CarProxy::CarProxy(BlockingQueue<std::string>& outqueue, float x, float y,
                      float angle, float size_x, float size_y, int id) :
                      outqueue(outqueue), x(x), y(y), angle(angle),
                      size_x(size_x), size_y(size_y), dead(false), id(id),
                      break_(false), life(0), was_contacted_last_tick(false) {}

void CarProxy::sendMethod(std::string method){
  outqueue.push("{\"type\": \"intent\", \"command\": \"" + method + "\"}");
}

void CarProxy::update(float x, float y, float angle, float size_x, float size_y,
  bool dead, bool break_, int life, bool was_contacted_last_tick){
  this->x = x;
  this->y = y;
  this->angle = angle;
  this->size_x = size_x;
  this->size_y = size_y;
  this->dead = dead;
  this->break_ = break_;
  this->life = life;
  this->was_contacted_last_tick = was_contacted_last_tick;
}

std::vector<float> CarProxy::GetPosition(){
  std::unique_lock<std::mutex> lock(m);
  std::vector<float> v;
  v.push_back(this->x);
  v.push_back(this->y);
  return v;
}

std::vector<float> CarProxy::GetSize(){
  std::unique_lock<std::mutex> lock(m);
  std::vector<float> v;
  v.push_back(this->size_x);
  v.push_back(this->size_y);
  return v;
}

float CarProxy::GetAngle(){
  return angle;
}

int CarProxy::GetId(){
  std::unique_lock<std::mutex> lock(m);
  return this->id;
}

int CarProxy::GetLife(){
  return life;
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
  std::unique_lock<std::mutex> lock(m);
  return this->dead;
}

void CarProxy::SteerCenter(){
  this->sendMethod("SteerCenter");
}

bool CarProxy::HasBreakOn(){
  return break_;
}

bool CarProxy::WasContactedLastTick() {
  return was_contacted_last_tick;
}
