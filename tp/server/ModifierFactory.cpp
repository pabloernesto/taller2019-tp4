#include "ModifierFactory.h"
#include "StoneCreator.h"
#include "BoostCreator.h"
#include "HealthBoxCreator.h"
#include "OilCreator.h"

ModifierFactory::ModifierFactory(){
  this->creators.emplace_back(new StoneCreator());
  this->creators.emplace_back(new BoostCreator());
  this->creators.emplace_back(new HealthBoxCreator());
  this->creators.emplace_back(new OilCreator());
}

Modifier* ModifierFactory::createModifier(int num, b2Vec2 size){
  return this->creators[num]->createModifier(size);
}


ModifierFactory::~ModifierFactory(){}
