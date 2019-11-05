#ifndef CONTACTABLE_H_
#define CONTACTABLE_H_

#include <Box2D/Box2D.h>

class Car;
class Posta;

class Contactable {
  public:
  Contactable(){};
  virtual void Contact(Contactable* contactable) = 0;
  virtual void GetContactedBy(Car* car) = 0;
  virtual void GetContactedBy(Posta* posta) = 0;

};

#endif  // CONTACTABLE_H_
