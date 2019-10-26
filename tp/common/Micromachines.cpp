/*#include "Micromachines.h"
#include <stdexcept>

#define CARTYPES {"red", "yellow", "blue"}

Micromachines::Micromachines(){
}

void Micromachines::addRace(std::string name, Track& track){
  this->races[name] = Race(track);
}

void Micromachines::removeRace(std::string name){
  this->races.erase(name);
}

void Micromachines::addCarToRace(std::string raceName, Car& car){
  this->races[raceName].AddCar(car);
}

std::map<std::string,Race>& Micromachines::getRaces(){
  return this->races;
}

void Micromachines::addRace(std::string name, Track& track){
  if (this->races.find(name) == this->races.end()){
    throw std::runtime_error("Nombre de carrera no disponible.");
  }
  this->races.emplace(name, track);
}

std::vector<std::string> Micromachines::getCarTypes(){
  return CARTYPES;
}*/