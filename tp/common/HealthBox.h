#ifndef _HEALTHBOX_H_
#define _HEALTHBOX_H_
#include "Modifier.h"
#include "Car.h"

class HealthBox : public Modifier{

  public:
    HealthBox(b2Vec2 size);
    virtual void Place(b2World& world, b2Vec2 position, float32 angle);
    virtual void Contact(Contactable* contactable);
    virtual void GetContactedBy(Car* car);
    virtual void GetContactedBy(Posta* posta);
    virtual void GetContactedBy(Modifier* modifier);
    virtual void modify(Car& car) override;
    virtual void removeModifierFromWorld();
    virtual std::string getType() override;
    virtual ~HealthBox();

};

#endif