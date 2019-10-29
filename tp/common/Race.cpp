#include "Race.h"

#include <Box2D/Box2D.h>

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

Race::Race(std::string track) : world((b2Vec2){ 0 , 0 }), cars(), 
  track(track, world), mainCar() {}

void Race::Step() {
  for (auto& car : cars) {
    car->Step();
  }
  this->world.Step(timestep, velocityIterations, positionIterations);
}

Car& Race::AddCar() {
  cars.emplace_back(new Car());
  b2Vec2 where = { 0, 0 };
  cars.back()->Place(world, where);
  return *cars.back();
}

Car& Race::AddMainCar() {
  b2Vec2 where = { 0, 0 };
  this->mainCar.Place(world, where);
  return this->mainCar;
}

std::vector<std::unique_ptr<Car>>& Race::GetCars() {
  return cars;
}

Car& Race::GetMainCar() {
  return this->mainCar;
}

Track& Race::GetTrack(){
  return this->track;
}