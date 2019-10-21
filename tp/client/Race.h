#ifndef RACE_H_
#define RACE_H_

#include "Car.h"
#include <vector>

class Race {
  std::vector<Car> cars;

public:
  void Step();
  void AddCar();
  std::vector<Car>& GetCars();
};

#endif    // RACE_H_
