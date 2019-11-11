#ifndef _STONE_H_
#define _STONE_H_
#include "Modifier.h"
#include "Car.h"

class Stone : public Modifier{

  static const float SPEED_REDUCTION;

  public:
    Stone(b2Vec2 size);
    virtual void Place(b2World& world, b2Vec2 position, float32 angle);
    virtual void Contact(Contactable* contactable);
    virtual void GetContactedBy(Car* car);
    virtual void GetContactedBy(Posta* posta);
    virtual void GetContactedBy(Modifier* modifier);
    virtual void modify(Car& car) override;
    virtual std::string getType() override;
    virtual ~Stone();

};

#endif
