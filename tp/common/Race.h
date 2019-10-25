#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include <vector>

class Race {
  b2World world;
  std::vector<Car> cars;

public:
  void Step();
  void AddCar();
  std::vector<Car>& GetCars();

  Race();
};

#endif    // RACE_H_
