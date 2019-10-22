#include "image.h"
#include <SDL2/SDL.h>
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

void Image::render() {
  // copy the whole image, occupy the entire screen
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void Image::render(SDL_Rect* where, double angle) {
  SDL_RenderCopyEx(renderer, texture, NULL, where, angle, NULL, SDL_FLIP_NONE);
}
