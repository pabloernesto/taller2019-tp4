#include "Car.h"

#include <Box2D/Box2D.h>

const b2Vec2 Car::CAR_SIZE(1.2, 2.5);
const float32 Car::WEIGHT_KG = 300;
const float32 Car::ENGINE_POWER = 10000;

Car::Car(): gas(false), life(1000){}

void Car::GasOn() {
  gas = true;
}

void Car::GasOff() {
  gas = false;
}

void Car::moveUp(){
  this->body->SetLinearVelocity(b2Vec2(0,1));
}

void Car::moveDown(){
  this->body->SetLinearVelocity(b2Vec2(0,-1));
}

void Car::moveLeft(){
  this->body->SetLinearVelocity(b2Vec2(-1,0));
}

void Car::moveRight(){
  this->body->SetLinearVelocity(b2Vec2(1,0));
}

void Car::Place(b2World& world, b2Vec2 position) {
  // Add car to the world
  b2BodyDef car_body_def;
  car_body_def.type = b2_dynamicBody;
  car_body_def.position = position;
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

const b2Vec2& Car::GetSize() {
  return CAR_SIZE;
}

void Car::Step() {
  if (gas) {
    b2Vec2 force = { 0, ENGINE_POWER };
    // Apply the force in the direction the car is facing
    b2Rot rotation(body->GetAngle());
    force = b2Mul(rotation, force);
    body->ApplyForceToCenter(force, true);
  }
}
