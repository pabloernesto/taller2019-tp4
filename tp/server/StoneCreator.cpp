#include "StoneCreator.h"
#include "Stone.h"

StoneCreator::StoneCreator(){}

Modifier* StoneCreator::createModifier(b2Vec2 size){
  return new Stone(size);
}

StoneCreator::~StoneCreator(){}