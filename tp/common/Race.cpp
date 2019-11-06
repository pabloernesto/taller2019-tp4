#include "Race.h"

#include <Box2D/Box2D.h>

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

Race::Race(std::string track, int laps) : world((b2Vec2){ 0 , 0 }), cars(), 
  track(track), listener(), postas(), laps(laps), ended(false){
    world.SetContactListener(&listener);
}

void Race::Step() {
  for (auto& car : cars) {
    car->Step(this->track);
  }
  this->world.Step(timestep, velocityIterations, positionIterations);
}

Car& Race::AddCar(float x, float y) {
  cars.emplace_back(new Car(this));
  b2Vec2 where = { x, y }; //position in metres
  cars.back()->Place(world, where);
  return *cars.back();
}

void Race::AddPosta(float x, float y, int id, float32 angle) {
  postas.emplace_back(new Posta(id));
  b2Vec2 where = { x, y }; //position in metres
  postas.back()->Place(world, where, angle);
}

std::vector<std::unique_ptr<Car>>& Race::GetCars() {
  return cars;
}

Track& Race::GetTrack(){
  return this->track;
}

std::vector<std::unique_ptr<TrackPiece>>& Race::getTrackPieces(){
  return this->track.getTrackPieces();
}

int Race::GetAmountOfPostas(){
  return postas.size();
}

int Race::GetLaps(){
  return laps;
}

void Race::SetWinner(Car* car){
  ended = true;
}

bool Race::Ended(){
  return ended;
}