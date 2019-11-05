#ifndef CONTACTABLE_H_
#define CONTACTABLE_H_

#include <Box2D/Box2D.h>

class Car;
class Posta;
class Modifier;

class Contactable {
  public:
  Contactable(){};
  virtual void Contact(Contactable* contactable) = 0;
  virtual void GetContactedBy(Car* car) = 0;
  virtual void GetContactedBy(Posta* posta) = 0;
  virtual void GetContactedBy(Modifier* modifier) = 0;

};

#endif  // CONTACTABLE_H_
