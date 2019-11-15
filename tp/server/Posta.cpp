#include "Posta.h"
#include "Configuration.h"

extern Configuration configuration;

Posta::Posta(int id, b2Vec2 position, float32 angle) :
  Contactable(), id(id), posta_size(configuration.POSTA_WIDTH, configuration.POSTA_HEIGHT), position(position), angle(angle) {}

void Posta::Contact(Contactable* contactable){
  contactable->GetContactedBy(this);
}

void Posta::GetContactedBy(Car* car){}

void Posta::GetContactedBy(Posta* posta){}

void Posta::GetContactedBy(Modifier* modifier){}

void Posta::Place(b2World& world) {
  // Add posta to the world
  b2BodyDef posta_body_def;
  posta_body_def.type = b2_staticBody;
  posta_body_def.position = position;
  posta_body_def.angle = angle;
  posta_body_def.userData = this;
  body = world.CreateBody(&posta_body_def);

  // Add collision and density to the posta
  b2PolygonShape shape_box;
  shape_box.SetAsBox(posta_size.x/2, posta_size.y/2);

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

float32 Posta::GetAngle(){
  return body->GetAngle();
}