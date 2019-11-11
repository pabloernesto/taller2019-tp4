#ifndef POSTA_H_
#define POSTA_H_

#include <Box2D/Box2D.h>
#include "Contactable.h"
#include <vector>

class Posta : public Contactable{
private:
  int id;
  b2Body* body;
  static const b2Vec2 POSTA_SIZE;
  b2Vec2 position; 
  float32 angle;

public:
  Posta(int id, b2Vec2 position, float32 angle);
  virtual void Contact(Contactable* contactable);
  virtual void GetContactedBy(Car* car);
  virtual void GetContactedBy(Posta* posta);
  virtual void GetContactedBy (Modifier* modifier);
  void Place(b2World& world);
  int GetId();
  b2Vec2 GetPosition();
  float32 GetAngle();
};

#endif  // POSTA_H_
