#include "Race.h"

#include <Box2D/Box2D.h>

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

Race::Race(Track& track) : world((b2Vec2){ 0 , 0 }), cars(), 
  track(track) {}

void Race::Step() {
  this->world.Step(timestep, velocityIterations, positionIterations);
}

void Race::AddCar() {
  this->cars.emplace_back();
  b2Vec2 where = { 0, 0 };
  cars.back().Place(world, where);
}

std::vector<Car>& Race::GetCars() {
  return cars;
}

Track& Race::GetTrack(){
  return this->track;
}