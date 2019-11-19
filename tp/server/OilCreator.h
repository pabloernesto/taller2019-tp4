#ifndef _OILCREATOR_H_
#define _OILCREATOR_H_
#include "ModifierCreator.h"

class OilCreator : public ModifierCreator {

  public: 
    OilCreator();
    virtual Modifier* createModifier(b2Vec2 size) override;
    virtual ~OilCreator();
};

#endif