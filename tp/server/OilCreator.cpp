#include "OilCreator.h"
#include "Oil.h"

OilCreator::OilCreator(){}

Modifier* OilCreator::createModifier(b2Vec2 size){
  return new Oil(size);
}

OilCreator::~OilCreator(){}