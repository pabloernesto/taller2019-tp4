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
  t(), filming(false)
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
  Shutdown();
  Join();
  videoOutput.close();
  sws_freeContext(videoContex);
}


void Filmer::Loop() {
  while (filming) {
    std::vector<char> data;
    if (!synchro.get(&data)) continue;
    videoOutput.writeFrame(data.data(), videoContex);
  }
}

SDL_Texture* Filmer::GetTexture(){
  return videoTexture;
}

void Filmer::FilmFrame() {
  if (!filming) return;

  int h;
  SDL_GetWindowSize(window, NULL, &h);
  std::vector<char> buffer(h * BUFFER_WIDTH * 3);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, buffer.data(), BUFFER_WIDTH * 3);
  synchro.tryset_dropold(std::move(buffer));
}

bool Filmer::IsFilming(){
  return filming;
}



// Thread control methods

void Filmer::Start() {
  filming = true;
  t = std::thread(&Filmer::Loop, this);
}

void Filmer::Shutdown() {
  filming = false;
  synchro.close();
}

void Filmer::Join() {
  if (t.joinable()) t.join();
}
