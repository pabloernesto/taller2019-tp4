#include "Posta.h"

const b2Vec2 Posta::POSTA_SIZE(15, 2);

Posta::Posta(int id) : 
  Contactable(), id(id) {}

void Posta::Contact(Contactable* contactable){
  contactable->GetContactedBy(this);
}

void Posta::GetContactedBy(Car* car){}

void Posta::GetContactedBy(Posta* posta){}

void Posta::GetContactedBy(Modifier* modifier){}

void Posta::Place(b2World& world, b2Vec2 position, float32 angle) {
  // Add posta to the world
  b2BodyDef posta_body_def;
  posta_body_def.type = b2_staticBody;
  posta_body_def.position = position;
  posta_body_def.angle = angle;
  posta_body_def.userData = this;
  body = world.CreateBody(&posta_body_def);

  // Add collision and density to the posta
  b2PolygonShape shape_box;
  shape_box.SetAsBox(POSTA_SIZE.x/2, POSTA_SIZE.y/2);

  b2FixtureDef posta_fixture_def;
  posta_fixture_def.shape = &shape_box;
  posta_fixture_def.density = 1;
  posta_fixture_def.isSensor = true; // For no physical collition
  body->CreateFixture(&posta_fixture_def);
}

int Posta::GetId(){
  return id;
}

b2Vec2 Posta::GetPosition(){
  return body->GetPosition();
}

int Posta::GetAngle(){
  return body->GetAngle();
}