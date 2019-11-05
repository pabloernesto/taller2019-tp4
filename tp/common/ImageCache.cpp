#include "ImageCache.h"

ImageCache::ImageCache(SDL_Window* w, SDL_Renderer* r)
  : window(w), renderer(r), images()
{}

Image& ImageCache::getImage(std::string path) {
  auto it = images.find(path);
  if (it != images.end()) return *it->second;

  // Didn't find path, load the image
  auto pair = images.emplace(
    path,
    std::unique_ptr<Image>(new Image(path.c_str(), window, renderer)));
  return *pair.first->second;
}

void ImageCache::LoadAnimation(std::string path, int w, int h, int ticks) {
  auto it = images.find(path);
  if (it != images.end()) throw std::runtime_error(path + " already loaded");
  
  images.emplace(
    path,
    std::unique_ptr<Image>(
      new Animation(path.c_str(), window, renderer, w, h, ticks)));
}

ImageCache::~ImageCache() {}
