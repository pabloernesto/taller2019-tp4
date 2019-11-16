#ifndef _HEALTH_BOX_CREATOR_H_
#define _HEALTH_BOX_CREATOR_H_
#include "ModifierCreator.h"

class HealthBoxCreator : public ModifierCreator{

  public:
    HealthBoxCreator();
    virtual Modifier* createModifier(b2Vec2 size) override;
    virtual ~HealthBoxCreator();

};

#endif