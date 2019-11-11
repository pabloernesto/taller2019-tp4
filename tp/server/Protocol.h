#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include "rapidjson/document.h"

rapidjson::Document Parse(std::string& x);

class Car;
std::string ToJSON(Car& x);

class Game;
std::string ToJSON(std::vector<Game>& x);

#endif  // PROTOCOL_H_
