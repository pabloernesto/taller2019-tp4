#ifndef _IMAGE_CACHE_H_
#define _IMAGE_CACHE_H_
#include <unordered_map>
#include <string>
#include "image.h"
#include <SDL2/SDL.h>
#include <memory>

class ImageCache {
  private:
    std::unordered_map<std::string, std::unique_ptr<Image>> images;
    std::unordered_map<std::string, std::string> alias_collection;
  public:
    ImageCache(SDL_Window* w, SDL_Renderer* r);
    Image& getImage(std::string image_path_or_alias);
    void loadAt(std::string alias, std::string path);
    ~ImageCache();
};

#endif
