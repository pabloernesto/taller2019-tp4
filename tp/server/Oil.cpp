#include "Oil.h"
#include <iostream>
#include "../common/Configuration.h"

extern Configuration configuration;

Oil::Oil(b2Vec2 size) : Modifier(size){}

void Oil::Place(b2World& world, b2Vec2 position, float32 angle){
  Modifier::Place(world, position, angle);
}

void Oil::Contact(Contactable* contactable){
  Modifier::Contact(contactable);
}

void Oil::GetContactedBy(Car* car){
  Modifier::GetContactedBy(car);
}

void Oil::GetContactedBy(Posta* posta){
  Modifier::GetContactedBy(posta);
}

void Oil::GetContactedBy(Modifier* modifier){
  Modifier::GetContactedBy(modifier);
}

void Oil::modify(Car& car){
  car.incrementAngularVelocity(configuration.OIL_INCREMENT, configuration.OIL_DURATION * configuration.FRAME_RATE);
}

std::string Oil::getType(){
  return "Oil";
}

Oil::~Oil(){}
