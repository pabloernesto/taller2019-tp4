#ifndef IMAGE_H_
#define IMAGE_H_
#include <SDL2/SDL.h>
#include <string>

// The tick parameter serves as synchronization information for animations,
// Image ignores it.
class Image {
protected:
  SDL_Renderer* renderer;
  SDL_Surface* image;
  SDL_Texture* texture;

public:
  Image(const char* path, SDL_Window* w, SDL_Renderer* r);
  virtual ~Image();

  // Render occupying the whole screen
  virtual void render(int tick);

  // Render to a certain part of the screen, at a certain angle
  // angle is clockwise, in degrees
  virtual void render(int tick, SDL_Rect* where, double angle);

  void ChangeColor();
};

// An Animation loads a single image from file, and iterprets it as a grid
// of individal frames
class Animation : public Image {
  // The grid is assumed to be w-by-h frames in size
  const int w;
  const int h;

  // Each frame is shown for this many ticks
  const int ticks;

public:
  // Render occupying the whole screen
  virtual void render(int tick);

  // Render to a certain part of the screen, at a certain angle
  // angle is clockwise, in degrees
  virtual void render(int tick, SDL_Rect* where, double angle);

  Animation(const char* path, SDL_Window* w, SDL_Renderer* r,
    int width, int height, int ticks);
};

#endif