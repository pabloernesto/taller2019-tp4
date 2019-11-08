#ifndef _MODIFIER_H_
#define _MODIFIER_H_

#include <Box2D/Box2D.h>
#include "Contactable.h"
#include <string>

class Modifier : public Contactable{

  private:
    b2Body* body;
    b2Vec2 size;

  public:
    Modifier(b2Vec2 size);
    virtual void Place(b2World& world, b2Vec2 position, float32 angle);
    virtual void Contact(Contactable* contactable) override;
    virtual void GetContactedBy(Car* car) override;
    virtual void GetContactedBy(Posta* posta) override;
    virtual void GetContactedBy(Modifier* modifier) override;
    virtual void modify(Car& car) = 0;
    virtual void removeModifierFromWorld();
    virtual bool isModifierOnWorld();
    virtual std::string getType() = 0;
    virtual b2Vec2 GetPosition();
    virtual b2Vec2 GetSize();
    virtual ~Modifier();
};

#endif
