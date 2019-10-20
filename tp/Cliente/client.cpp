#include <SDL2/SDL.h>
//#include "../common/Event.h"
#include "client.h"
#include "inicio.h"
//#include "../common/socket.h"

Client::Client() /*INICIAR SOCKET*/{
}

Client::~Client(){
  SDL_Quit();
}

void Client::start() {
  /*CONECTAR SOCKET*/
  SDL_Init(SDL_INIT_EVERYTHING);
  Inicio inicio;
  inicio.start();
/*
  Connection connection("localhost", "1234");
  while (true) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) break;

    if (sdl_event.type == SDL_KEYDOWN) {
      KeyEvent event(SDL_GetKeyName(sdl_event.key.keysym.sym));
      connection.SendStr(event.ToStr().c_str());
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();*/
}