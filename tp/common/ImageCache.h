#ifndef _IMAGE_CACHE_H_
#define _IMAGE_CACHE_H_
#include <unordered_map>
#include <string>
#include "image.h"
#include <SDL2/SDL.h>
#include <memory>

class ImageCache {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::unordered_map<std::string, std::unique_ptr<Image>> images;

public:
  Image& getImage(std::string path);
  void LoadAnimation(std::string path, int w, int h, int ticks);

  ImageCache(SDL_Window* w, SDL_Renderer* r);
  ~ImageCache();
};

#endif
