#include "Camara.h"
#include "MKStoPixel.h"
#include <math.h>

Camara::Camara(int x, int y, int w, int h, Car& car): camara({x,y,w,h}),
  mainBody(car){}

void Camara::Update(){
  auto&& pixelPosition = MKStoPixelTransform(this->mainBody.GetPosition());
  this->camara.x =  pixelPosition.x - camara.w/2;
  this->camara.y = -pixelPosition.y - camara.h/2;
}

SDL_Rect Camara::GetPosition(){
  return this->camara;
}

void Camara::renderMe(b2Vec2 position, b2Vec2 size, Image& image, float angle){
  // Object radius
  auto&& objsize_pixels = MKStoPixelTransform(size);
  float objradius_pixels = objsize_pixels.Length();

  // Screen radius
  float screenradius_pixels = sqrt(pow(camara.w / 2, 2) + pow(camara.h / 2, 2));

  // Distance between centers
  auto&& objcenterpos_pixels = MKStoPixelTransform(position);
  objcenterpos_pixels.y = - objcenterpos_pixels.y;
  b2Vec2 screencenterpos_pixels = {
    (float) (camara.x + camara.w / 2),
    (float) (camara.y + camara.h / 2)
  };
  float objcamdist_pixels =
    (objcenterpos_pixels - screencenterpos_pixels).Length();

  if (objcamdist_pixels < objradius_pixels + screenradius_pixels) {
    b2Vec2 objcorner = objcenterpos_pixels - 0.5 * objsize_pixels;
    // Relative position, in pixels, of the object and camera's _corners_
    SDL_Rect where = {
      (int) objcorner.x - camara.x,
      (int) objcorner.y - camara.y,
      (int) objsize_pixels.x,
      (int) objsize_pixels.y
    };
    // The car image points downward, add 180 degrees to flip it up
    image.render(&where, 180 + angle * RADIANS_TO_DEGREES_FACTOR);
  }
}