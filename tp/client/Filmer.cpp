#include "Filmer.h"
#include <stdexcept>
#include <vector>
#define FILENAME "demo.mp4"
extern "C" {
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}
#include "../common/Configuration.h"

extern Configuration configuration;

#include <iostream>

Filmer::Filmer(SDL_Window* window, SDL_Renderer* renderer) : 
  window(window), renderer(renderer), context(), 
  videoOutput(context, FILENAME, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT)
{
  videoTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, 
    SDL_TEXTUREACCESS_TARGET, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT);
  videoContex = sws_getContext(configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT, 
    AV_PIX_FMT_RGB24, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT, 
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
  std::vector<char> dataBuffer(configuration.WINDOW_WIDTH * configuration.WINDOW_HEIGHT*3);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), configuration.WINDOW_WIDTH * 3);
  videoOutput.writeFrame(dataBuffer.data(), videoContex);
}