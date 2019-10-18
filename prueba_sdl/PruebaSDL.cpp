#include <SDL2/SDL.h>

int main(int argc, char** argv){

    // Start SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a Window in the middle of the screen
    SDL_Window *window = nullptr;
    window = SDL_CreateWindow("Hello World!",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // x and y
            640, 480, // Width and Height
            SDL_WINDOW_SHOWN);

    // Delay so that we can see the window appear
    SDL_Delay(2000);

    // Cleanup and Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
