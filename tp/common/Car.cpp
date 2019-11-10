#include "Car.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "Race.h"

#define NUMBEROFFRAMESDYING 20

const b2Vec2 Car::CAR_SIZE(1.2, 2.5);
const float32 Car::WEIGHT_KG = 300;
const float32 Car::ENGINE_POWER = 20000;
const float Car::MAX_SPEED = 14;
const float Car::MAX_SPEED_REV = 6;
const float32 Car::ANGULAR_VEL_MULT = 0.2;
const float32 Car::FRICTION = 2;
const size_t Car::EXPLODING_SEC_LIMIT = 5;
const size_t Car::LIFE = 5;
const size_t Car::SPEED_RED_TIME_SEC = 3;

Car::Car(int id, Race* race)
  : Contactable(), id(id), body(), gas(false), break_(false), reverse(false),
  life(LIFE), max_speed(MAX_SPEED), angular_velocity(0), step_counter(0),
  step_counter_death(0), step_counter_max_speed_mult(0),
  max_speed_multiplier(1), speed_reducer(0), step_counter_red_speed(0), lastPosta(new Posta(-1)),
  dead(false), race(race), laps(0)
{}

void Car::GasOn() {
  gas = true;
}

void Car::GasOff() {
  gas = false;
}

void Car::reverseOn() {
  reverse = true;
}

void Car::reverseOff() {
  reverse = false;
}

bool Car::isGoingReverse() {
  return reverse;
}

bool Car::stopped(){
  return (this->GetSpeed() <= 1) && (this->GetSpeed() >= -1);
}

void Car::BreakOn() {
  break_ = true;
}

void Car::BreakOff() {
  break_ = false;
}

void Car::SteerLeft() {
  // steer = 'l';
  angular_velocity = ANGULAR_VEL_MULT;
}

void Car::SteerRight() {
  // steer = 'r';
  angular_velocity = -ANGULAR_VEL_MULT;
}

void Car::SteerCenter() {
  // steer = 'c';
  angular_velocity = 0;
}

void Car::Place(b2World& world, b2Vec2 position) {
  // Add car to the world
  b2BodyDef car_body_def;
  car_body_def.type = b2_dynamicBody;
  car_body_def.position = position;
  car_body_def.linearDamping = FRICTION;
  car_body_def.userData = this;
  body = world.CreateBody(&car_body_def);

  // Add collision and density to the car
  b2PolygonShape collision_box;
  collision_box.SetAsBox(CAR_SIZE.x/2, CAR_SIZE.y/2);

  b2FixtureDef car_fixture_def;
  car_fixture_def.shape = &collision_box;
  const float32 DENSITY = WEIGHT_KG / (CAR_SIZE.x * CAR_SIZE.y);
  car_fixture_def.density = DENSITY;
  body->CreateFixture(&car_fixture_def);
}

const b2Vec2& Car::GetPosition() {
  return body->GetPosition();
}

float Car::GetAngle() {
  return body->GetAngle();
}

const b2Vec2& Car::GetSize() {
  return CAR_SIZE;
}

void Car::setCounter(size_t value){
  // std::cout << "Setting counter\n";
  this->step_counter = value;
}

void Car::updateCounter(size_t value){
  // std::cout << "I'm in car!! About to update car counter\n";
  this->step_counter += value;
  // if (this->step_counter > 30){
    // this->step_counter = 30;
  // }
  // std::cout << "I'm in car!! Updated car counter\n";
}

void Car::updateMaxSpeedMultiplier(){
  if (this->step_counter_max_speed_mult > 0){
    // The effect is still active
    this->step_counter_max_speed_mult -= 1;
  } else {
    // The effect is not active
    this->max_speed_multiplier = 1;
  }
}

void Car::multiplyMaxSpeed(float multiplier, size_t steps){
  this->step_counter_max_speed_mult = steps;
  this->max_speed_multiplier = multiplier;
}

void Car::updateMaxSpeed(){
  // The game updates 60 times per second.
  // 1 frame (step) equals to 1/60 seconds.
  // 500 ms equals to 1/2 second.
  // So, at 30 steps the speed should be half its original value.
  
  size_t counter = this->step_counter;
  if (counter > 30)
    counter = 30;
  // Max posible value is 30.

  if (this->reverse){
    this->max_speed = (- (MAX_SPEED_REV) / (2 * 30) * (counter)) + MAX_SPEED_REV; 
  } else{
    this->max_speed = (- (MAX_SPEED) / (2 * 30) * (counter)) + MAX_SPEED;
  }
  this->updateMaxSpeedMultiplier();
  this->max_speed = this->max_speed * this->max_speed_multiplier;
  // It's a linear function that fulfills two points: (0, MAX_SPEED) and (30, MAX_SPEED/2)
  // where "x" is step_counter and "y" is max_speed. 
}

float Car::getReducedSpeed(float speed_recv){
  float speed = speed_recv;
  if (speed > 0){
      speed -= this->speed_reducer;
      if (speed < 0)
        speed = 0;
  } else if (speed < 0){
    speed += this->speed_reducer;
    if (speed > 0)
      speed = 0;
  }
  if (this->step_counter_red_speed > 0){
    this->step_counter_red_speed -= 1;
  } else {
    this->speed_reducer = 0;
  }
  //The effect is applied once. So, it's setted to 0.
  return speed;
}

void Car::Step(Track& track) {
  track.updateCarCounter(*this);
  // std::cout << this->step_counter <<"\n";
  this->updateMaxSpeed();
  body->SetAngularVelocity(this->angular_velocity * this->GetSpeed());

  // Realign velocity to car's facing
  {
    b2Rot rotation(body->GetAngle());
    b2Vec2 facing(0, 1);
    facing = b2Mul(rotation, facing);
    float speed = this->GetSpeed();
    
    // To contemplate the speed reducer
    speed = this->getReducedSpeed(speed);

    body->SetLinearVelocity(speed * facing);
  }

  b2Vec2 force;
  if (break_) {
    auto speed = GetSpeed();
    if (speed == 0){
      return;
    } else if (speed < 0){
      force = { 0, ENGINE_POWER};
    } else if (speed > 0){
      force = { 0, -ENGINE_POWER };
    }
  } else if (gas) {
    if (reverse) {
      force = { 0, -ENGINE_POWER};
    } else {
      force = { 0, ENGINE_POWER };
    }
  }
  // Apply the force in the direction the car is facing
  b2Rot rotation(body->GetAngle());
  force = b2Mul(rotation, force);
  body->ApplyForceToCenter(force, true);

  // Taking into consideration that we have a 60fps.
  if (life <= 0 || (this->step_counter >= (60 * EXPLODING_SEC_LIMIT))){
    this->DieAndRevive(track);
  }
}

const b2Transform& Car::GetTransform(){
  return this->body->GetTransform();
}

// This function returns the car's speed along the direction it faces
float Car::GetSpeed() {
  auto& velocity = body->GetLinearVelocity();

  // facing is a unit vector pointing the same way as the car
  b2Rot rotation(body->GetAngle());
  b2Vec2 facing(0, 1);
  facing = b2Mul(rotation, facing);

  // return the projection of velocity along car facing
  float v = b2Dot(velocity, facing);
  if (reverse){
    if (v < -this->max_speed){
      return -this->max_speed;
    }
  }
  if (v > this->max_speed)
    return this->max_speed;
  return v;
}

bool Car::isGoingForward(){
  return (this->GetSpeed() >= 0);
}

void Car::restoreLife(){
  this->life = LIFE;
}

void Car::reduceLife(){
  this->life -= 1;
}

void Car::reduceSpeed(float speed_reduction){
  this->speed_reducer = speed_reduction;
  this->step_counter_red_speed = SPEED_RED_TIME_SEC;
}

void Car::Contact(Contactable* contactable){
  contactable->GetContactedBy(this);
}

void Car::GetContactedBy(Car* car){
  life -= 1;
}

void Car::GetContactedBy(Posta* posta){
  if (((lastPosta->GetId() + 1)%race->GetAmountOfPostas()) == posta->GetId()){
    *lastPosta = *posta;
    if (lastPosta->GetId() == 0){
      ++laps;
    }
    if (laps - 1 == race->GetLaps()){
      race->SetWinner(this);
    }
  }
}

void Car::GetContactedBy(Modifier* modifier){
  // The car contacts the modifier. Not the other way around. So, the call
  // to modify() is done in Modifier::GetContactedBy(Car* car).
}

void Car::DieAndRevive(Track& track){
  if (dead == false){
    dead = true;
    step_counter_death = NUMBEROFFRAMESDYING;
  }
  if (step_counter_death == 0) {
    body->SetTransform(lastPosta->GetPosition(), lastPosta->GetAngle());
    life = LIFE;
    this->setCounter(0);
    dead = false;
  } else {
    step_counter_death--;
  }
}

bool Car::isDead(){
  return dead;
}

int Car::GetId(){
  return id;
}