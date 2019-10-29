#ifndef CAMARA_H_
#define CAMARA_H_

#include <SDL2/SDL.h>
#include "Car.h"

class Camara{
  SDL_Rect camara;
  Car& mainBody;

public:
  Camara(int x, int y, int h, int w, Car& car);
  void Update();
  SDL_Rect GetPosition();
private:
  b2Vec2 MKStoPixelTransform(const b2Vec2& vector);
};

#endif 