#include "HealthBox.h"


HealthBox::HealthBox(b2Vec2 size) : Modifier(size){}

void HealthBox::Place(b2World& world, b2Vec2 position, float32 angle){
  Modifier::Place(world, position, angle);
}

void HealthBox::Contact(Contactable* contactable){
  Modifier::Contact(contactable);
}

void HealthBox::GetContactedBy(Car* car){
  Modifier::GetContactedBy(car);
}

void HealthBox::GetContactedBy(Posta* posta){
  Modifier::GetContactedBy(posta);
}

void HealthBox::GetContactedBy(Modifier* modifier){
  Modifier::GetContactedBy(modifier);
}

void HealthBox::modify(Car& car){
  car.restoreLife();
}

HealthBox::~HealthBox(){}
