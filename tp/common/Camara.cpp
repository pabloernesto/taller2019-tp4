#include "Camara.h"

/************************************
 * AUXILIAR
 ***********************************/
const int PIXELS_PER_METER = 100;
// Box2D measures angles counter-clockwise, and SDL does it clockwise
// Shove in a -1 factor to account for that
const float RADIANS_TO_DEGREES_FACTOR = (-1) * 360.0 / (2 * 3.1415);

b2Vec2 Camara::MKStoPixelTransform(const b2Vec2& vector) {
  b2Vec2 v = {PIXELS_PER_METER * vector.x, PIXELS_PER_METER * vector.y};
  return v;
}

/************************************
 * PRIMITIVAS
 * **********************************/

Camara::Camara(int x, int y, int w, int h, Car& car): camara({x,y,w,h}),
  mainBody(car){}

void Camara::Update(){
  auto&& p = this->MKStoPixelTransform(this->mainBody.GetPosition());
  this->camara.x = p.x;;
  this->camara.y = p.y;;
}

SDL_Rect Camara::GetPosition(){
  return this->camara;
}