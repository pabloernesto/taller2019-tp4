#include "Race.h"

#include <Box2D/Box2D.h>

void Race::Step() {}

void Race::AddCar() {
  cars.emplace_back();
  b2Vec2 where = { 0, 0 };
  cars.end()->Place(world, where);
}

std::vector<Car>& Race::GetCars() {
  return cars;
}

Race::Race() : world((b2Vec2){ 0 , 0 }), cars() {}
