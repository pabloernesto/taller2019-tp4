#include "Modifier.h"
#include <iostream>


Modifier::Modifier(b2Vec2 size) : size(size), should_be_removed(false){}

void Modifier::Place(b2World& world, b2Vec2 position, float32 angle) {
  // Add modifier to the world
  b2BodyDef modif_body_def;
  modif_body_def.type = b2_staticBody;
  modif_body_def.position = position;
  modif_body_def.angle = angle;
  modif_body_def.userData = this;
  body = world.CreateBody(&modif_body_def);

  // Add collision and density to the modifier
  b2PolygonShape shape_box;
  shape_box.SetAsBox(this->size.x/2, this->size.y/2);

  b2FixtureDef modif_fixture_def;
  modif_fixture_def.shape = &shape_box;
  modif_fixture_def.density = 1;
  modif_fixture_def.isSensor = true; // For no physical collition
  body->CreateFixture(&modif_fixture_def);
}

void Modifier::Contact(Contactable* contactable){
  contactable->GetContactedBy(this);
}


void Modifier::GetContactedBy(Car* car){
  this->modify(*car);
  this->should_be_removed = true;
}

void Modifier::GetContactedBy(Posta* posta){}

void Modifier::GetContactedBy(Modifier* modifier){}

bool Modifier::shouldBeRemoved(){
  return this->should_be_removed;
}

b2Vec2 Modifier::GetPosition(){
  return this->body->GetPosition();
}

b2Vec2 Modifier::GetSize(){
  return this->size;
}

Modifier::~Modifier(){
  this->body->GetWorld()->DestroyBody(this->body);
}