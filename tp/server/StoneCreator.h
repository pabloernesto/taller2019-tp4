#ifndef _STONE_CREATOR_H_
#define _STONE_CREATOR_H_
#include "ModifierCreator.h"

class StoneCreator : public ModifierCreator{
  public:
    StoneCreator();
    virtual Modifier* createModifier(b2Vec2 size) override;
    virtual ~StoneCreator();

};

#endif
