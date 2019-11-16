#ifndef _BOOST_CREATOR_H_
#define _BOOST_CREATOR_H_
#include "ModifierCreator.h"

class BoostCreator : public ModifierCreator{

  public:
    BoostCreator();
    virtual Modifier* createModifier(b2Vec2 size) override;
    virtual ~BoostCreator();

};

#endif
