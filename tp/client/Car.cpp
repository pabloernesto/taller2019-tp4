#include "Car.h"

#include <Box2D/Box2D.h>

const float32 Car::WIDTH_METERS = 1.2;
const float32 Car::LENGTH_METERS = 2.5;
const float32 Car::WEIGHT_KG = 300;

void Car::GasOn() {
  gas = true;
}

void Car::GasOff() {
  gas = false;
}

void Car::Place(b2World& world, b2Vec2 position) {
  // Add car to the world
  b2BodyDef car_body_def;
  car_body_def.type = b2_dynamicBody;
  car_body_def.position = position;
  body = world.CreateBody(&car_body_def);

  // Add collision and density to the car
  b2PolygonShape collision_box;
  collision_box.SetAsBox(WIDTH_METERS/2, LENGTH_METERS/2);

  b2FixtureDef car_fixture_def;
  car_fixture_def.shape = &collision_box;
  const float32 DENSITY = WEIGHT_KG / (WIDTH_METERS * LENGTH_METERS);
  car_fixture_def.density = DENSITY;
  body->CreateFixture(&car_fixture_def);
}

const b2Vec2& Car::GetPosition() {
  return body->GetPosition();
}
