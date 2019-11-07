#include "Race.h"

#include <Box2D/Box2D.h>
#include <chrono>
#include <random>

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;
const int MODIFIERS_AVAILABLE = 3;
const size_t MODIFIER_DIST_DROP = 30;
const size_t MODIFIER_RESET_SEC = 5;
const b2Vec2 MODIF_SIZE = { 1 , 1 };

Race::Race(std::string track, int laps)
  : world((b2Vec2){ 0 , 0 }), cars(), track(track), listener(), postas(),
  modifiers_reset(MODIFIER_RESET_SEC*60), modif_factory(), laps(laps),
  ended(false)
{
  world.SetContactListener(&listener);
}

void Race::Step() {
  for (auto& car : cars) {
    car->Step(this->track);
  }
  if (modifiers_reset == 0){
    this->placeModifiers();
    modifiers_reset = MODIFIER_RESET_SEC*60;
  } else {
    modifiers_reset -= 1;
  }
  this->world.Step(timestep, velocityIterations, positionIterations);
}

void Race::placeModifiers(){
  size_t vec_size = this->modifiers.size();
  for (size_t i = 0; i < vec_size; i++){
    this->modifiers.pop_back();
  }
  for (auto it = this->cars.begin(); it != this->cars.end(); it++){
    const b2Transform& car_trans = (*it)->GetTransform();
    b2Vec2 car_pos = car_trans.p;
    b2Rot car_angle = car_trans.q;
    // By trigonometry:
    // car_angle.c = cos(car_angle) and car_angle.s = sin(car_angle)
    float modif_x = (car_angle.c) * (car_pos.Length() + MODIFIER_DIST_DROP);
    float modif_y = (car_angle.s) * (car_pos.Length() + MODIFIER_DIST_DROP);
    this->placeRandomModifier(modif_x, modif_y);
  }
}

void Race::placeRandomModifier(float x, float y){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, MODIFIERS_AVAILABLE - 1);
  int number = distribution(generator);
  b2Vec2 pos = { x , y};
  Modifier* mod = this->modif_factory.createModifier(number, MODIF_SIZE);
  mod->Place(this->world, pos, 0);
  this->modifiers.emplace_back(mod);
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