#include "Filmer.h"
#include <stdexcept>
#include <vector>
#define FILENAME "demo.mp4"
extern "C" {
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

const int BUFFER_WIDTH = 608, BUFFER_HEIGHT = 400;

Filmer::Filmer(SDL_Window* window, SDL_Renderer* renderer) : 
  window(window), renderer(renderer), context(), 
  videoOutput(context, FILENAME, BUFFER_WIDTH, BUFFER_HEIGHT),
  videoTexture(), videoContex(),
  filming(false)
{
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  videoTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, 
    SDL_TEXTUREACCESS_TARGET, w, h);
  videoContex = sws_getContext(w, h, AV_PIX_FMT_RGB24, BUFFER_WIDTH, BUFFER_HEIGHT, 
    AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
}

Filmer::~Filmer(){
  videoOutput.close();
  sws_freeContext(videoContex);
}

SDL_Texture* Filmer::GetTexture(){
  return videoTexture;
}

void Filmer::FilmFrame(){
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  std::vector<char> dataBuffer(BUFFER_WIDTH*h*3);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), BUFFER_WIDTH * 3);
  //videoOutput.writeFrame(dataBuffer.data(), videoContex);
}

void Filmer::StartFilming(){
  filming = true;
}

bool Filmer::IsFilming(){
  return filming;
}