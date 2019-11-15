#include "BoostCreator.h"
#include "Boost.h"

BoostCreator::BoostCreator(){}

Modifier* BoostCreator::createModifier(b2Vec2 size){
  return new Boost(size);
}

BoostCreator::~BoostCreator(){}