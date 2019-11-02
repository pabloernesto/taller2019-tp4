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
  Car mainCar;

public:
  Race(std::string track);
  void Step();
  Car& AddCar();
  std::vector<std::unique_ptr<Car>>& GetCars();
  Car& GetMainCar();
  Track& GetTrack();

  Race();
};

#endif    // RACE_H_
