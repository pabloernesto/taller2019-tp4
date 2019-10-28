#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include "Track.h"
#include <vector>
#include <memory>   // unique_ptr

class Race {
  b2World world;
  std::vector<std::unique_ptr<Car>> cars;
  Track track;

public:
  Race(Track& track);
  void Step();
  Car& AddCar();
  std::vector<std::unique_ptr<Car>>& GetCars();
  Track& GetTrack();

  Race();
};

#endif    // RACE_H_
