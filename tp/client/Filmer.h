#ifndef FILMER_H
#define FILMER_H

#include <SDL2/SDL.h>
#include "FormatContext.h"
#include "OutputFormat.h"
#include <thread>
#include <atomic>
#include "../common/FrameDropper.h"
#include <vector>

class Filmer {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  FormatContext context;
  OutputFormat videoOutput;
  SDL_Texture* videoTexture;
  SwsContext * videoContex;

  std::thread t;
  std::atomic<bool> filming;

  void Loop();

public:
  FrameDropper<std::vector<char>> synchro;

  Filmer(SDL_Window* window, SDL_Renderer* renderer);
  ~Filmer();
  SDL_Texture* GetTexture();
  void FilmFrame();
  bool IsFilming();

  // Thread control methods
  void Start();
  void Shutdown();
  void Join();
};

#endif    // FILMER_H