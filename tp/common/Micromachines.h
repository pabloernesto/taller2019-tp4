/*#ifndef MICROMACHINES_H_
#define MICROMACHINES_H_
#include "Event.h"
#include <string>
#include <vector>
#include <map>
#include "Race.h"
#include "Track.h"
#include "Car.h"

class Micromachines{
private:
  std::map<std::string,Race> races;
  std::vector<Track> tracks;
  
public:
  Micromachines();
  void addRace(std::string name, Track& track);
  void removeRace(std::string name);
  void addCarToRace(std::string raceName, Car& car);
  std::map<std::string,Race>& getRaces();
  std::vector<std::string> getCarTypes();
};

#endif*/