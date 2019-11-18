#include <SDL2/SDL.h>
#include <stdexcept>    // runtime_error

class App {
public:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Color
    background { 0, 0, 0, 0 },
    foreground { 255, 255, 255, 0 };

  App() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
      "This window is resizeable!",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,   // x, y
      120, 120,                                         // w, h
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) throw std::runtime_error("Window creation failed");

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) throw std::runtime_error("Renderer creation failed");
  }

  void start() {
    while (true) {
      SDL_Event e;
      if (!SDL_WaitEvent(&e)) throw std::runtime_error("SDL_WaitEvent error");
      
      if (e.type == SDL_QUIT) break;
      else if (e.type == SDL_WINDOWEVENT) HandleWindowEvent(e);
    }
  }

  ~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

private:
  void render() {
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, foreground.r, foreground.g, foreground.b, foreground.a);
    SDL_Rect rect = { 100, 100, 40, 40 };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
  }

  void HandleWindowEvent(SDL_Event& e) {
    if (e.window.event == SDL_WINDOWEVENT_EXPOSED) render();
    else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) render();
  }
};

int main(int argc, char** argv) {
  App().start();
}
