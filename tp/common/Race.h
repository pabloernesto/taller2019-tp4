#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include "Track.h"
#include <vector>

class Race {
  b2World world;
  std::vector<Car> cars;
  Track track;

public:
  Race(Track& track);
  void Step();
  void AddCar(Car& car);
  std::vector<Car>& GetCars();
  Track& GetTrack();

  Race();
};

#endif    // RACE_H_
