#include "ModifierView.h"
#include "../common/MKStoPixel.h"
#include <math.h>

ModifierView::ModifierView(Image& image, Modifier& modifier, Camara& camara)
  : image(image), modifier(modifier), camara(camara){}

void ModifierView::render(int tick) {
  b2Vec2 position = this->modifier.GetPosition();

  camara.renderMe(
    position,
    this->modifier.GetSize(),
    this->image,
    0,
    tick);
}
