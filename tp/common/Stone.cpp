#include "Stone.h"

const float Stone::SPEED_REDUCTION = 4;

Stone::Stone(b2Vec2 size) : Modifier(size){}

void Stone::Place(b2World& world, b2Vec2 position, float32 angle){
  Modifier::Place(world, position, angle);
}

void Stone::Contact(Contactable* contactable){
  Modifier::Contact(contactable);
}

void Stone::GetContactedBy(Car* car){
  Modifier::GetContactedBy(car);
}

void Stone::GetContactedBy(Posta* posta){
  Modifier::GetContactedBy(posta);
}

void Stone::GetContactedBy(Modifier* modifier){
  Modifier::GetContactedBy(modifier);
}

void Stone::modify(Car& car){
  // Asuming 60 fps
  car.reduceLife();
  car.reduceSpeed(SPEED_REDUCTION);
}

void Stone::removeModifierFromWorld(){
  Modifier::removeModifierFromWorld();
}

std::string Stone::getType(){
  return "Stone";
}

Stone::~Stone(){}
