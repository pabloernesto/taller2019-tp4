#include "Camara.h"
#include "MKStoPixel.h"
#include <math.h>

Camara::Camara(int x, int y, int w, int h, CarProxy& car): camara({x,y,w,h}),
  mainBody(car){}

void Camara::Update(){
  std::vector<float> position;
  position.push_back(this->mainBody.GetPosition()[0]);
  position.push_back(this->mainBody.GetPosition()[1]);
  auto&& pixelPosition = MKStoPixelTransform(position);
  this->camara.x =  pixelPosition[0] - camara.w/2;
  this->camara.y = -pixelPosition[1] - camara.h/2;
}

SDL_Rect Camara::GetPosition(){
  return this->camara;
}

void Camara::renderMe(std::vector<float> position, std::vector<float> size, Image& image, 
  std::vector<Mix_Chunk*>& sounds, float angle, int tick)
{
  // Object radius
  auto&& objsize_pixels = MKStoPixelTransform(size);
  float x = objsize_pixels[0];
  float y = objsize_pixels[1];
  float objradius_pixels = sqrt(x * x + y * y);

  // Screen radius
  float screenradius_pixels = sqrt(pow(camara.w / 2, 2) + pow(camara.h / 2, 2));

  // Distance between centers
  auto&& objcenterpos_pixels = MKStoPixelTransform(position);
  objcenterpos_pixels[1] = - objcenterpos_pixels[1];
  std::vector<float> screencenterpos_pixels = {
    (float) (camara.x + camara.w / 2),
    (float) (camara.y + camara.h / 2)
  };

  float xobjcam = objcenterpos_pixels[0] - screencenterpos_pixels[0];
  float yobjcam = objcenterpos_pixels[1] - screencenterpos_pixels[1];
  float objcamdist_pixels = sqrt(xobjcam * xobjcam + yobjcam * yobjcam);

  if (objcamdist_pixels < objradius_pixels + screenradius_pixels) {
    std::vector<double> objcorner = {objcenterpos_pixels[0] - 0.5 * objsize_pixels[0],
                                  objcenterpos_pixels[1] - 0.5 * objsize_pixels[1]};
    // Relative position, in pixels, of the object and camera's _corners_
    SDL_Rect where = {
      (int) objcorner[0] - camara.x,
      (int) objcorner[1] - camara.y,
      (int) objsize_pixels[0],
      (int) objsize_pixels[1]
    };
    image.render(tick, &where, angle * RADIANS_TO_DEGREES_FACTOR);
  }

  for (auto& sound : sounds){
    Mix_PlayChannel(-1, sound, 0);
  }
}