#include "Boost.h"
#include <iostream>
#include "Configuration.h"

extern Configuration configuration;

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
  car.multiplyMaxSpeed(configuration.BOOST_MULT, 
    configuration.BOOST_DURATION_SEC * configuration.FRAME_RATE);
}

std::string Boost::getType(){
  return "Boost";
}

Boost::~Boost(){}
