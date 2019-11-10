#include "Protocol.h"
#include "rapidjson/document.h"
#include "../common/Car.h"

rapidjson::Document Parse(std::string& x) {
  rapidjson::Document d;
  d.Parse(x.c_str());
  return d;
}

std::string ToJSON(Car& x) {}
