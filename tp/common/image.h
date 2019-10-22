#ifndef IMAGE_H_
#define IMAGE_H_
#include <SDL2/SDL.h>
#include <string>

class Image {
private:
  SDL_Renderer* renderer;
  SDL_Surface* image;
  SDL_Texture* texture;

public:
  Image(const char* path, SDL_Window* w, SDL_Renderer* r);
  ~Image();

  // Render occupying the whole screen
  void render();

  // Render to a certain part of the screen, at a certain angle
  // angle is clockwise, in degrees
  void render(SDL_Rect* where, double angle);
};

#endif