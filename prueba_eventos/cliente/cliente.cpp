#include <SDL2/SDL.h>
#include "../common/socket.h"

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);

  // Create a Window in the middle of the screen
  SDL_Window *window = SDL_CreateWindow(
    "Hello World!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // x and y
    640, 480,                                       // Width and Height
    SDL_WINDOW_SHOWN);

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
  SDL_Quit();
}
