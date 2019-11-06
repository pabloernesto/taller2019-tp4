#ifndef _MODIFIER_FACTORY_H_
#define _MODIFIER_FACTORY_H_
#include "Modifier.h"
#include "ModifierCreator.h"
#include <vector>

class ModifierFactory {

  private:
    std::vector<std::unique_ptr<ModifierCreator>> creators;

  public:
    ModifierFactory();
    Modifier* createModifier(int num, b2Vec2 size);

    ~ModifierFactory();
};

#endif
