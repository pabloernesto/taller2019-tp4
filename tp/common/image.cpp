#include "image.h"
#include <SDL2/SDL.h>
#include <string>

Image::Image(const char* path, SDL_Window* &w, SDL_Renderer* &r)
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

void Image::render(int x, int y, int height, int width){
  SDL_Rect dstrect = {x, y, width, height};
  SDL_RenderCopy(this->renderer, this->texture, NULL, &dstrect);
}