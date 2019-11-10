#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include "rapidjson/document.h"

rapidjson::Document Parse(std::string& x);

class Car;
std::string ToJSON(Car& x);

#endif  // PROTOCOL_H_
