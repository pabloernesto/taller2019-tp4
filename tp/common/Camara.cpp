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
  float objradius_pixels = sqrt(pow(objsize_pixels.x/2, 2) + pow(objsize_pixels.y/2, 2));

  // Screen radius
  float screenradius_pixels = sqrt(pow(camara.w / 2, 2) + pow(camara.h / 2, 2));

  // Distance between centers
  auto&& objcenterpos_pixels = MKStoPixelTransform(position);
  objcenterpos_pixels.y = - objcenterpos_pixels.y;
  pixel_vect_s screencenterpos_pixels = { camara.x + camara.w / 2, camara.y + camara.h / 2};
  pixel_vect_s obj_pos_rel_camera_pixels = {
    objcenterpos_pixels.x - screencenterpos_pixels.x,
    objcenterpos_pixels.y - screencenterpos_pixels.y
  };
  float objcamdist_pixels = sqrt(
    pow(obj_pos_rel_camera_pixels.x / 2, 2)
    + pow(obj_pos_rel_camera_pixels.y / 2, 2));

  if (objcamdist_pixels < objradius_pixels + screenradius_pixels) {
    pixel_vect_s objcorner = {
      objcenterpos_pixels.x - objsize_pixels.x / 2,
      objcenterpos_pixels.y - objsize_pixels.y / 2
    };
    // Relative position, in pixels, of the object and camera's _corners_
    SDL_Rect where = {
      objcorner.x - camara.x,
      objcorner.y - camara.y,
      objsize_pixels.x,
      objsize_pixels.y
    };
    // The car image points downward, add 180 degrees to flip it up
    image.render(&where, 180 + angle * RADIANS_TO_DEGREES_FACTOR);
  }
}