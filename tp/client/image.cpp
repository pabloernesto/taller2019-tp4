#include "image.h"
#include <string>

Image::Image(const char* path, SDL_Window* w, SDL_Renderer* r)
  : renderer(r),
  image(SDL_LoadBMP(path)),
  texture(SDL_CreateTextureFromSurface(r, image))
{
  if (!image)
    SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), w);
  if (!texture)
    SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), w);
}

Image::~Image(){
  SDL_DestroyTexture(this->texture);
  SDL_FreeSurface(this->image);
}

void Image::render(SDL_Renderer* renderer){
    SDL_Rect dstrect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, this->texture, NULL, &dstrect);
}