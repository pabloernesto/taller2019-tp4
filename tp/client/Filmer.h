#ifndef FILMER_H
#define FILMER_H

#include <SDL2/SDL.h>
#include "FormatContext.h"
#include "OutputFormat.h"

class Filmer {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  FormatContext context;
  OutputFormat videoOutput;
  SDL_Texture* videoTexture;
  SwsContext * videoContex;
  bool filming;

public:
  Filmer(SDL_Window* window, SDL_Renderer* renderer);
  ~Filmer();
  SDL_Texture* GetTexture();
  void FilmFrame();
  void StartFilming();
  void StopFilming();
  bool IsFilming();
};

#endif    // FILMER_H