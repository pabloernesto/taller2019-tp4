#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <memory>   // unique_ptr

rapidjson::Document Parse(std::string& x);

class Car;
std::string ToJSON(Car& x);

class Modifier;
std::string ToJSON(std::vector<std::unique_ptr<Modifier>>& x);

class Game;
std::string ToJSON(std::vector<std::unique_ptr<Game>>& x);

class Race;
std::string ToJSON(Race& x);

#endif  // PROTOCOL_H_
