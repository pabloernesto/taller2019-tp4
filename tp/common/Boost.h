#ifndef _BOOST_H_
#define _BOOST_H_
#include "Modifier.h"
#include "Car.h"

class Boost : public Modifier{

  static const float BOOST_MULT;
  static const size_t BOOST_DURATION_SEC;

  public:
    Boost(b2Vec2 size);
    virtual void Place(b2World& world, b2Vec2 position, float32 angle);
    virtual void Contact(Contactable* contactable);
    virtual void GetContactedBy(Car* car);
    virtual void GetContactedBy(Posta* posta);
    virtual void GetContactedBy(Modifier* modifier);
    virtual void modify(Car& car) override;
    virtual std::string getType() override;
    virtual ~Boost();

};

#endif
