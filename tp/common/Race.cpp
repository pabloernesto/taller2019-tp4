#include "Race.h"

#include <Box2D/Box2D.h>

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

Race::Race() : world((b2Vec2){ 0 , 0 }), cars() {}

void Race::Step() {
  this->world.Step(timestep, velocityIterations, positionIterations);
}

void Race::AddCar() {
  cars.emplace_back();
  b2Vec2 where = { 0, 0 };
  cars.back().Place(world, where);
}

std::vector<Car>& Race::GetCars() {
  return cars;
}