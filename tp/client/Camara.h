#ifndef CAMARA_H_
#define CAMARA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "CarProxy.h"
#include "image.h"
#include <vector>

class Camara{
  SDL_Rect camara;
  CarProxy& mainBody;

public:
  Camara(int x, int y, int w, int h, CarProxy& car);
  void Update();
  SDL_Rect GetPosition();
  void renderMe(std::vector<float> position, std::vector<float> size, Image& image, 
  std::vector<Mix_Chunk*>& sounds, float angle, int tick);
};

#endif