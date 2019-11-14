#ifndef MODIFIERVIEW_H_
#define MODIFIERVIEW_H_

#include <SDL2/SDL.h>
#include "ModifierProxy.h"
#include "image.h"
#include "Camara.h"
#include <vector>

class ModifierView {
  ModifierProxy& modifier;
  Image& image;
  Camara& camara;

public:
  virtual void render(int tick);
  ModifierView(Image& image, ModifierProxy& modifier, Camara& camara);
};


#endif
