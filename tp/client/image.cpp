#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

Image::Image(const char* path, SDL_Window* w, SDL_Renderer* r)
  : renderer(r),
  image(IMG_Load(path)),
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

void Image::render(int tick) {
  // copy the whole image, occupy the entire screen
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void Image::render(int tick, SDL_Rect* where, double angle) {
  SDL_RenderCopyEx(renderer, texture, NULL, where, angle, NULL, SDL_FLIP_NONE);
}

void Image::ChangeColor(){
  Uint8 r;
  Uint8 g;
  Uint8 b;
  SDL_GetTextureColorMod(texture, &r, &g, &b);
  std::cout << "r: " << r+40 << " g: " << g+40 << " b: " << b+40 << "\n";
  SDL_SetTextureColorMod(texture, r+40, g+40, b+40);
}
