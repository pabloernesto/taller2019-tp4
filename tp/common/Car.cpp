#include "Car.h"

#include <Box2D/Box2D.h>

const b2Vec2 Car::CAR_SIZE(1.2, 2.5);
const float32 Car::WEIGHT_KG = 300;
const float32 Car::ENGINE_POWER = 10000;

Car::Car(): gas(false), break_(false), steer('c'), life(1000) {}

void Car::GasOn() {
  gas = true;
}

void Car::GasOff() {
  gas = false;
}

void Car::BreakOn() {
  break_ = true;
}

void Car::BreakOff() {
  break_ = false;
}

void Car::SteerLeft() {
  steer = 'l';
}

void Car::SteerRight() {
  steer = 'r';
}

void Car::SteerCenter() {
  steer = 'c';
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

float Car::GetAngle() {
  return body->GetAngle();
}

const b2Vec2& Car::GetSize() {
  return CAR_SIZE;
}

void Car::Step() {
  if (steer == 'c') {
    body->SetAngularVelocity(0);
  } else if (steer == 'l') {
    body->SetAngularVelocity(8);
  } else if (steer == 'r') {
    body->SetAngularVelocity(-8);
  }

  // Realign velocity to car's facing
  b2Rot rotation(body->GetAngle());
  b2Vec2 facing(0, 1);
  facing = b2Mul(rotation, facing);
  body->SetLinearVelocity(GetSpeed() * facing);

  if (break_) {
    auto speed = GetSpeed();
    if (speed <= 0) return;

    b2Vec2 force = { 0, -ENGINE_POWER };

    // Apply the force opposite the direction the car is facing
    b2Rot rotation(body->GetAngle());
    force = b2Mul(rotation, force);
    body->ApplyForceToCenter(force, true);

  } else if (gas) {
    b2Vec2 force = { 0, ENGINE_POWER };
    // Apply the force in the direction the car is facing
    b2Rot rotation(body->GetAngle());
    force = b2Mul(rotation, force);
    body->ApplyForceToCenter(force, true);
  }
}

// This function returns the car's speed along the direction it faces
float Car::GetSpeed() {
  auto& velocity = body->GetLinearVelocity();

  // facing is a unit vector pointing the same way as the car
  b2Rot rotation(body->GetAngle());
  b2Vec2 facing(0, 1);
  facing = b2Mul(rotation, facing);

  // return the projection of velocity along car facing
  return b2Dot(velocity, facing);
}
