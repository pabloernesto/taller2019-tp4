#ifndef _MODIFIER_CREATOR_H_
#define _MODIFIER_CREATOR_H_
#include "Modifier.h"

class ModifierCreator{

  public:
    ModifierCreator();
    virtual Modifier* createModifier(b2Vec2 size) = 0;
    virtual ~ModifierCreator();

};

#endif
