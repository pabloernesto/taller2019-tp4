#include "HealthBoxCreator.h"
#include "HealthBox.h"

HealthBoxCreator::HealthBoxCreator(){}

Modifier* HealthBoxCreator::createModifier(b2Vec2 size){
  return new HealthBox(size);
}

HealthBoxCreator::~HealthBoxCreator(){}