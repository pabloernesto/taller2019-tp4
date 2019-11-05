#include "image.h"

#include <SDL2/SDL.h>

Animation::Animation(const char* path, SDL_Window* w, SDL_Renderer* r,
    int width, int height, int ticks)
  : Image(path, w, r), w(width), h(height), ticks(ticks)
{}

void Animation::render(int tick) {
  render(tick, NULL, 0);
}

void Animation::render(int tick, SDL_Rect* where, double angle) {
  const int nframes = w * h;
  const int frame = (tick / ticks) % nframes;
  const int frame_width = image->w / w;
  const int frame_height = image->h / h;

  SDL_Rect from = {
    frame_width * (frame % w),    frame_height * (frame / w),
    frame_width,                  frame_height
  };

  SDL_RenderCopyEx(renderer, texture, &from, where, angle, NULL, SDL_FLIP_NONE);
}
