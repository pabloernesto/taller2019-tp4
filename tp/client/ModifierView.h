#ifndef MODIFIERVIEW_H_
#define MODIFIERVIEW_H_

#include <SDL2/SDL.h>
#include "../common/Modifier.h"
#include "image.h"
#include "Camara.h"
#include <vector>

class ModifierView {
  Modifier& modifier;
  Image& image;
  Camara& camara;

public:
  virtual void render(int tick);
  ModifierView(Image& image, Modifier& modifier, Camara& camara);
};


#endif
