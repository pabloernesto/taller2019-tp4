#ifndef CAMARA_H_
#define CAMARA_H_

#include <SDL2/SDL.h>
#include "Car.h"
#include "image.h"

class Camara{
  SDL_Rect camara;
  Car& mainBody;

public:
  Camara(int x, int y, int h, int w, Car& car);
  void Update();
  SDL_Rect GetPosition();
  void renderMe(b2Vec2 position, b2Vec2 size, Image& image, float angle);
};

#endif 