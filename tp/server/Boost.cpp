#include "Boost.h"
#include <iostream>

const float Boost::BOOST_MULT = 1.3;
const size_t Boost::BOOST_DURATION_SEC = 3;
const size_t Boost ::FPS = 60;

Boost::Boost(b2Vec2 size) : Modifier(size){}

void Boost::Place(b2World& world, b2Vec2 position, float32 angle){
  Modifier::Place(world, position, angle);
}

void Boost::Contact(Contactable* contactable){
  Modifier::Contact(contactable);
}

void Boost::GetContactedBy(Car* car){
  Modifier::GetContactedBy(car);
}

void Boost::GetContactedBy(Posta* posta){
  Modifier::GetContactedBy(posta);
}

void Boost::GetContactedBy(Modifier* modifier){
  Modifier::GetContactedBy(modifier);
}

void Boost::modify(Car& car){
  // Asuming 60 fps
  car.multiplyMaxSpeed(BOOST_MULT, BOOST_DURATION_SEC * FPS);
}

std::string Boost::getType(){
  return "Boost";
}

Boost::~Boost(){}
