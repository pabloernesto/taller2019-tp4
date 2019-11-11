#include "Protocol.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../common/Car.h"

rapidjson::Document Parse(std::string& x) {
  rapidjson::Document d;
  d.Parse(x.c_str());
  return d;
}

std::string ToJSON(Car& x) {
  rapidjson::Document d;
  d.AddMember("id", x.GetId(), d.GetAllocator());
  d.AddMember("position.x", x.GetPosition().x, d.GetAllocator());
  d.AddMember("position.y", x.GetPosition().y, d.GetAllocator());
  d.AddMember("angle", x.GetAngle(), d.GetAllocator());
  // TODO: get life

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  return std::string(buffer.GetString());
}
