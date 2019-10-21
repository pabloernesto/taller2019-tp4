#ifndef IMAGE_H_
#define IMAGE_H_
#include <SDL2/SDL.h>
#include <string>

class Image{
private:
  SDL_Renderer* renderer;
  SDL_Surface* image;
  SDL_Texture* texture;

public:
  Image(const char* path, SDL_Window* w, SDL_Renderer* r);
  ~Image();

  void render(SDL_Renderer* renderer, int x, int y, int heightm, int width);
};

#endif