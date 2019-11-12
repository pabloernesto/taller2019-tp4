#include "ModifierView.h"
#include "MKStoPixel.h"
#include <math.h>

ModifierView::ModifierView(Image& image, Modifier& modifier, Camara& camara)
  : modifier(modifier), image(image), camara(camara) {}

void ModifierView::render(int tick) {
  std::vector<float> position = {this->modifier.GetPosition().x, this->modifier.GetPosition().y};
  std::vector<float> size = {this->modifier.GetSize().x, this->modifier.GetSize().y};

  camara.renderMe(
    position,
    size,
    this->image,
    0,
    tick);
}
