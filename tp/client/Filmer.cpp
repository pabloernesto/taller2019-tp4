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
  videoOutput(context, FILENAME, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT),
  videoTexture(), videoContex(),
  t(), filming(false)
{
  videoTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, 
    SDL_TEXTUREACCESS_TARGET, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT);
  videoContex = sws_getContext(configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT, 
    AV_PIX_FMT_RGB24, configuration.WINDOW_WIDTH, configuration.WINDOW_HEIGHT, 
    AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
}

Filmer::~Filmer(){
  Shutdown();
  Join();
  videoOutput.close();
  sws_freeContext(videoContex);
}


void Filmer::Loop() {
  while (filming) {
    std::vector<char>* data;
    if (!synchro.Consume(&data)) continue;
    videoOutput.writeFrame(data->data(), videoContex);
  }
}

SDL_Texture* Filmer::GetTexture(){
  return videoTexture;
}

void Filmer::FilmFrame() {
  if (!filming) return;

  auto& buffer = synchro.GetBuffer();
  int h;
  SDL_GetWindowSize(window, NULL, &h);
  buffer.reserve(h * configuration.WINDOW_WIDTH * 3);

  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, buffer.data(), configuration.WINDOW_WIDTH * 3);
  synchro.Produce();
}

bool Filmer::IsFilming(){
  return filming;
}



// Thread control methods

void Filmer::Start() {
  filming = true;
  synchro.open();
  t = std::thread(&Filmer::Loop, this);
}

void Filmer::Shutdown() {
  filming = false;
  synchro.close();
}

void Filmer::Join() {
  if (t.joinable()) t.join();
}
