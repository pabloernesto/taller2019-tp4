#include "Race.h"
#include <Box2D/Box2D.h>
#include <chrono>
#include <random>
#include "Configuration.h"

extern Configuration configuration;

Race::Race(std::string track, int laps, std::vector<std::unique_ptr<Posta>>* postas)
  : world(b2Vec2(0, 0)), cars(), postas(postas), modifiers(), modif_factory(),
  track(track), listener(), modifiers_reset(configuration.MODIFIER_RESET_SEC*60), laps(laps),
  ended(false), winnerCar(), modif_size(configuration.MODIFIER_WIDTH, configuration.MODIFIER_HEIGHT) {
  world.SetContactListener(&listener);
  std::vector<std::unique_ptr<Posta>>::iterator it = postas->begin();
  for (;it != postas->end(); ++it){
    (*it)->Place(world);
  }
}

void Race::Step() {
  for (auto& car : cars) {
    car->Step(this->track);
  }
  if (this->modifiers_reset == 0){
    this->placeModifiers();
    modifiers_reset = configuration.MODIFIER_RESET_SEC*60;
  } else {
    modifiers_reset -= 1;
  }
  this->removeUsedModifiers();
  this->world.Step(configuration.TIME_STEP, configuration.VELOCITY_ITERATIONS, 
    configuration.POSITION_ITERATIONS);
}

void Race::removeUsedModifiers(){
  auto it = this->modifiers.begin();
  while (it != this->modifiers.end()){
    if ( (*it)->shouldBeRemoved()){
      it = this->modifiers.erase(it);
    } else {
      it++;
    }
  }
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
    b2Vec2 dist = { 0 , configuration.MODIFIER_DIST_DROP };
    b2Vec2 new_dist = (b2Mul(car_angle, dist)) + car_pos;
    // By trigonometry:
    // car_angle.c = cos(car_angle) and car_angle.s = sin(car_angle)
    this->placeRandomModifier(new_dist.x, new_dist.y);
  }
}

void Race::placeRandomModifier(float x, float y){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, configuration.MODIFIERS_AVAILABLE - 1);
  int number = distribution(generator);
  b2Vec2 pos = { x , y};
  Modifier* mod = this->modif_factory.createModifier(number, modif_size);
  mod->Place(this->world, pos, 0);
  this->modifiers.emplace_back(mod);
}

Car& Race::AddCar(float x, float y, int id) {
  cars.emplace_back(new Car(id, this));
  b2Vec2 where = { x, y }; //position in metres
  cars.back()->Place(world, where);
  return *cars.back();
}

Car& Race::AddNewCarToRace(){
  b2Vec2 where;
  if (cars.size() == 0 ){
    where = { 5 , -25 };
    //WARNING: HARDCODED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  } else {
    where = cars.back()->GetPosition();
    where.x += 3;
  }
  return this->AddCar(where.x, where.y, cars.size()+1);
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

std::vector<std::unique_ptr<Modifier>>& Race::getModifiers(){
  return this->modifiers;
}

int Race::GetAmountOfPostas(){
  return postas->size();
}

int Race::GetLaps(){
  return laps;
}

void Race::SetWinner(Car* car){
  ended = true;
  winnerCar = car;
}

bool Race::Ended(){
  return ended;
}

int Race::GetIdWinnerCar(){
  return winnerCar->GetId();
}