#ifndef CLIENT_H_
#define CLIENT_H_
#include <SDL2/SDL.h>
#include <string>

class Client{
private:
  SDL_Surface* imagen;
  SDL_Texture* textura;
  int x;
  int y;

public:
  Client();
  ~Client();

  void start();
};

#endif