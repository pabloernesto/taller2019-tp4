#include "ModifierView.h"
#include "MKStoPixel.h"
#include <math.h>

ModifierView::ModifierView(Image& image, ModifierProxy& modifier, Camara& camara)
  : modifier(modifier), image(image), camara(camara) {}

void ModifierView::render(int tick) {
  std::vector<float> position = this->modifier.GetPosition();
  std::vector<float> size = this->modifier.GetSize();
  std::vector<Mix_Chunk*> sounds = {};

  camara.renderMe(
    position,
    size,
    this->image,
    sounds,
    0,
    tick);
}
