#include "Camara.h"
#include "MKStoPixel.h"
#include <math.h>

Camara::Camara(int x, int y, int w, int h, Car& car): camara({x,y,w,h}),
  mainBody(car){}

void Camara::Update(){
  auto&& pixelSize = MKStoPixelTransform(this->mainBody.GetSize());
  auto&& pixelPosition = MKStoPixelTransform(this->mainBody.GetPosition());
  this->camara.x = pixelPosition.x + pixelSize.x/2 - camara.w/2;
  this->camara.y = pixelPosition.y - pixelSize.y/2 + camara.h/2;
}

SDL_Rect Camara::GetPosition(){
  return this->camara;
}

void Camara::renderMe(b2Vec2 position, b2Vec2 size, Image& image, float angle){
  auto&& pixelSize = MKStoPixelTransform(size);
  auto&& pixelPosition = MKStoPixelTransform(position);
  float maxLength = sqrt(pow(pixelSize.x/2, 2) + pow(pixelSize.y/2, 2));
  bool isAboveInferiorBorder = (pixelPosition.y + maxLength) > (camara.y - camara.h);
  bool isBelowSuperiorBorder = (pixelPosition.y - maxLength) < camara.y;
  bool isInsideRightBorder = (pixelPosition.x + maxLength) > camara.x;
  bool isInsideLeftBorder = (pixelPosition.x - maxLength) < camara.x + camara.w;
  
  if (isAboveInferiorBorder && isBelowSuperiorBorder && isInsideRightBorder && isInsideLeftBorder){
      SDL_Rect where = {
        (int) pixelPosition.x - camara.x, (int) -pixelPosition.y + camara.y,   // due to coordinate change, minus-y-coordinate
        (int) pixelSize.x, (int) pixelSize.y
      };
      // The car image points downward, add 180 degrees to flip it up
      image.render(&where, 180 + angle * RADIANS_TO_DEGREES_FACTOR);
  }
}