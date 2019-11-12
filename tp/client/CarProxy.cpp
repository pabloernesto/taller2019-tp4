#include "CarProxy.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

void CarProxy::sendMethod(std::string method){
  rapidjson::Document d;
  d.AddMember("type", "intent", d.GetAllocator());
  rapidjson::Value command (method.c_str(), d.GetAllocator());
  d.AddMember("command", command, d.GetAllocator());
  
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  // Como pusheo y a donde pusheo (el buffer)???
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

void CarProxy::SteerCenter(){
  this->sendMethod("SteerCenter");
}